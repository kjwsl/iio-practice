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

    GnssListener::GnssListener(const string_view gnss_path, const GnssCallback cb, const int& buf_size, const int& max_events) {
        set_path(gnss_path);
        set_callback(cb);
        set_buf_size(buf_size);
        set_max_events(max_events);
    }

    GnssListener::~GnssListener(){
        if (m_gnss_fd != -1) {
            close(m_gnss_fd);
            m_gnss_fd = -1;
        }

    }

    void GnssListener::start() {
        if (m_is_running) {
            cout << "GnssListener is already running" << endl;
            return;
        }

        m_is_running = true;
        m_thread = thread{&GnssListener::_run, this};
    }

    void GnssListener::stop() {
        if (!m_is_running) {
            cout << "GnssLister is not running" << endl;
            return;
        }

        m_is_running = false;
        if (m_thread.joinable()) {
            m_thread.join();
            if (m_gnss_fd == -1) {
                close(m_gnss_fd);
                m_gnss_fd = -1;
            }
        }
    }

    void GnssListener::set_path(string_view new_path) {
        if (new_path.empty()){
            throw invalid_argument { "Path is empty" };
        }

        if (m_is_running) {
            throw runtime_error { "You're trying to set path while it's running" };
        }


        m_gnss_path = new_path;
    }

    void GnssListener::set_callback(GnssCallback cb) {
        if (cb == nullptr) {
            throw invalid_argument{"Callback is nullptr"};
        }

        if (m_is_running) {
            throw runtime_error { "You're trying to set callback while it's running" };
        }

        m_cb = cb;
    }


    void GnssListener::set_buf_size(const int& size) {
        if (size < 1) {
            cout << "Buffer size must be greater than 1, defaults to " << m_buf_size << "." << endl;
            m_buf_size = DEFAULT_BUFF_SIZE;
            return;
        }

        if (m_is_running) {
            throw runtime_error{"You're trying to set buffer size while it's running" };
        }

        m_buf_size = size;
    }
    
    void GnssListener::set_max_events(const int& event_cnt) {
        if (event_cnt < 1) {
            cout << "Max num of events must be greater than 1, defaults to " << m_max_events << "." << endl;
            m_max_events = DEFAULT_MAX_EVENT_CNT;
            return;
        }

        if (m_is_running) {
            throw runtime_error{"You're trying to set max events while it's running" };
        }


        m_max_events = event_cnt;
    }

    void GnssListener::_run() {
        m_gnss_fd = open(m_gnss_path.data(), O_RDONLY | O_NONBLOCK | O_NDELAY | O_NOCTTY);
        if (m_gnss_fd == -1) {
            assert("File descriptor of GNSS, or epoll is empty somehow");
        }

        int epoll_fd { epoll_create1(0) };
        if (epoll_fd == -1) {
            throw ios_base::failure { "Failed to create epoll instance" };
        }

        epoll_event epoll_request {
            .events = EPOLLIN,
            .data = {
                .fd = m_gnss_fd,
            }
        };

        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, m_gnss_fd, &epoll_request) == -1) {
            throw runtime_error { "Failed to add Gnss fd to epoll watchlist" };
        }

        vector<epoll_event> epoll_evts(m_max_events);


        while(m_is_running) {
            int event_cnt { epoll_wait(epoll_fd, epoll_evts.data(), m_max_events, m_timeout) };
            if (event_cnt == -1) {
                if (errno == EINTR) {
                    continue;
                }
                break;
            }


            for (int i = 0; i < event_cnt; i++) {
                if (epoll_evts[i].data.fd == m_gnss_fd) {
                    string buffer{};
                    buffer.resize(m_buf_size);

                    lseek(m_gnss_fd, 0, SEEK_SET);
                    ssize_t bytes_read = read(m_gnss_fd, buffer.data(), buffer.size());
                    m_cb(bytes_read, buffer);
                    buffer.clear();
                    // printf("Sensor value: %s\n", buffer);
                }
            }
        }
    }
}
