
#include <memory>
#include <string_view>

namespace gnss::impl{

    using namespace std;

    class GnssListener {
        public:
            GnssListener() = delete;
            virtual ~GnssListener() = default;

            GnssListener(string_view gnss_path, const int& buf_size = 64, const int& max_events = 10);

            void start();
            void stop();
            void set_path(string_view new_path);

        private:
            int m_gnss_fd{0};
            int m_epoll_fd{0};
            int m_buf_size;
            int m_max_events;

            void _setup(string_view path);
    };
}

