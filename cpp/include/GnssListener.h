#ifndef __GNSS_LISTENER_H__
#define __GNSS_LISTENER_H__

#include <memory>
#include <string_view>
#include <thread>
#include <functional>
#include <sys/epoll.h>
namespace gnss::impl{

    using namespace std;

    class GnssListener {
        public:
            using GnssCallback = function<void(ssize_t, char[])>;

            GnssListener() = delete;
            virtual ~GnssListener() = default;

            GnssListener(string_view gnss_path, GnssCallback cb, const int& buf_size = 64, const int& max_events = 10);

            void start();
            void stop();
            void set_path(string_view new_path);
            void set_callback(GnssCallback cb);

        private:
            string_view m_gnss_path;
            int m_buf_size;
            int m_max_events;
            // TODO: Should timeout be configurable?
            int m_timeout{1000};
            int m_callback;
            bool m_is_running{false};
            thread m_thread;
            GnssCallback m_cb;

            void _on_received();
            void _run();
    };
}


#endif // __GNSS_LISTENER_H__
