#include <cassert>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <fcntl.h>
#include <thread>

#include "include/GnssListener.h"

namespace gnss::impl {
    using namespace std; 

    GnssListener::GnssListener(string_view gnss_path, GnssCallback cb ,const int& buf_size, const int& max_events)
        : m_cb(cb) {
        if (gnss_path.empty()) {
            throw invalid_argument{ "GNSS path can't be empty."};
        }
        if (!cb) {
            throw invalid_argument{ "Valid GNSS callback has to be given." };
        }
        if (buf_size < 1) {
            cout << "Buffer size must be greater than 1, defaults to " << m_buf_size << "." << endl;
        }

        if (max_events < 1) {
            cout << "Max num of events must be greater than 1, defaults to " << m_max_events << "." << endl;
        }

        m_buf_size = buf_size;
        m_max_events = max_events;
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
        }
    }

    void GnssListener::set_path(string_view new_path){
        if (new_path.empty()){
            throw invalid_argument { "Path is empty" };
        }
        m_gnss_path = new_path;
    }

    void GnssListener::set_callback(GnssCallback cb) {
        if (cb == nullptr) {
            throw invalid_argument{"Callback is nullptr"};
        }
        m_cb = cb;
    }

    void GnssListener::_run() {
        int gnss_fd {open(m_gnss_path.data(), O_RDONLY | O_NONBLOCK | O_NDELAY | O_NOCTTY)};
        if (gnss_fd == -1) {
            assert("File descriptor of GNSS, or epoll is empty somehow");
        }

        int epoll_fd { epoll_create1(0) };
        if (epoll_fd == -1) {
            throw ios_base::failure { "Failed to create epoll instance" };
        }

        epoll_event epoll_request {
            .events = EPOLLIN,
            .data.fd = gnss_fd,
        };

        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, gnss_fd, &epoll_request) == -1) {
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
                if (epoll_evts[i].data.fd == gnss_fd) {
                    lseek(gnss_fd, 0, SEEK_SET);

                    char buffer[m_buf_size];

                    ssize_t bytes_read = read(gnss_fd, buffer, sizeof(buffer) - 1);
                    buffer[bytes_read] = '\0';
                    m_cb(bytes_read, buffer);
                    // printf("Sensor value: %s\n", buffer);
                }
            }
        }
    }
}
