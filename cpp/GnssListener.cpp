#include <cassert>
#include <ios>
#include <iostream>
#include <string>
#include <stdexcept>
#include <unistd.h>
#include <fcntl.h>
#include <thread>

#include "include/GnssListener.h"

namespace gnss::impl {
    using namespace std; 

    GnssListener::GnssListener(const string_view gnssPath, const GnssCallback& callback, const int& bufferSize, const int& maxEvents) {
        setPath(gnssPath);
        setCallback(callback);
        setBufSize(bufferSize);
        setMaxEvents(maxEvents);
    }

    GnssListener::~GnssListener() {
        if (mGnssFd != -1) {
            close(mGnssFd);
            mGnssFd = -1;
        }

    }

    void GnssListener::start() {
        if (mIsRunning) {
            cout << "GnssListener is already running" << endl;
            return;
        }

        mIsRunning = true;
        mThread = thread{&GnssListener::run_, this};
    }

    void GnssListener::stop() {
        if (!mIsRunning) {
            cout << "GnssLister is not running" << endl;
            return;
        }

        mIsRunning = false;
        if (mThread.joinable()) {
            mThread.join();
            if (mGnssFd == -1) {
                close(mGnssFd);
                mGnssFd = -1;
            }
        }
    }

    void GnssListener::setPath(string_view newPath) {
        if (newPath.empty()){
            throw invalid_argument { "Path is empty" };
        }

        if (mIsRunning) {
            throw runtime_error { "You're trying to set path while it's running" };
        }


        mGnssPath = newPath;
    }

    void GnssListener::setCallback(GnssCallback cb) {
        if (cb == nullptr) {
            throw invalid_argument{"Callback is nullptr"};
        }

        if (mIsRunning) {
            throw runtime_error { "You're trying to set callback while it's running" };
        }

        mCallback = cb;
    }


    void GnssListener::setBufSize(const int& size) {
        if (size < 1) {
            cout << "Buffer size must be greater than 1, defaults to " << mBufferSize << "." << endl;
            mBufferSize = DEFAULT_BUFF_SIZE;
            return;
        }

        if (mIsRunning) {
            throw runtime_error{"You're trying to set buffer size while it's running" };
        }

        mBufferSize = size;
    }
    
    void GnssListener::setMaxEvents(const int& eventCnt) {
        if (eventCnt < 1) {
            cout << "Max num of events must be greater than 1, defaults to " << mMaxEvents << "." << endl;
            mMaxEvents = DEFAULT_MAX_EVENT_CNT;
            return;
        }

        if (mIsRunning) {
            throw runtime_error{"You're trying to set max events while it's running" };
        }


        mMaxEvents = eventCnt;
    }

    void GnssListener::run_() {
        mGnssFd = open(mGnssPath.data(), O_RDONLY | O_NONBLOCK | O_NDELAY | O_NOCTTY);
        if (mGnssFd == -1) {
            assert("File descriptor of GNSS, or epoll is empty somehow");
        }

        int epoll_fd { epoll_create1(0) };
        if (epoll_fd == -1) {
            throw ios_base::failure { "Failed to create epoll instance" };
        }

        epoll_event epoll_request {
            .events = EPOLLIN,
            .data = {
                .fd = mGnssFd,
            }
        };

        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, mGnssFd, &epoll_request) == -1) {
            throw runtime_error { "Failed to add Gnss fd to epoll watchlist" };
        }

        vector<epoll_event> epollEvts(mMaxEvents);


        GnssEventHandler eventHandler{ };
        while (mIsRunning) {
            int eventCnt { epoll_wait(epoll_fd, epollEvts.data(), mMaxEvents, mTimeout) };
            if (eventCnt == -1) {
                if (errno == EINTR) {
                    continue;
                }
                break;
            }

            eventHandler.clear();
            string buffer {};
            buffer.resize(mBufferSize);
            for (int i = 0; i < eventCnt; i++) {
                if (epollEvts[i].data.fd == mGnssFd) {
                    lseek(mGnssFd, 0, SEEK_SET);
                    ssize_t bytes_read = read(mGnssFd, buffer.data(), buffer.size());
                    if (bytes_read <= 0) continue;
                    eventHandler.writeToBuffer(buffer.data());
                }
            }
            while(eventHandler.hasNextNmeaSentence()) {
                const auto& sentence { eventHandler.extractNmeaSentence()};
                if (sentence == nullopt) {
                    // This doesn't make sense, but just in case
                    continue;
                }
                thread([this, sentence](){
                        mCallback(sentence.value());
                        });

            }
        }
    }
}
