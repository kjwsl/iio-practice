#ifndef __GNSS_LISTENER_H__
#define __GNSS_LISTENER_H__

#include <memory>
#include <string_view>
#include <thread>
#include <functional>
#include <sys/epoll.h>

#include "Constants.h"

namespace gnss::impl{

    using namespace std;

    class GnssListener {
        public:
            using GnssCallback = function<void(ssize_t, string)>;

            GnssListener() = delete;
            virtual ~GnssListener();

            GnssListener(const string_view gnss_path, const GnssCallback cb, const int& buf_size = DEFAULT_BUFF_SIZE, const int& max_events = DEFAULT_MAX_EVENT_CNT);

            void start();
            void stop();
            void set_path(const string_view new_path);
            void set_callback(const GnssCallback cb);
            void set_buf_size(const int& size);
            void set_max_events(const int& event_cnt);

        private:
            string_view m_gnss_path;
            int m_gnss_fd;
            int m_buf_size;
            int m_max_events;
            GnssCallback m_cb;
            // TODO: Should timeout be configurable?
            int m_timeout{1000};
            bool m_is_running{false};
            thread m_thread;

            void _run();
    };
}


#endif // __GNSS_LISTENER_H__
