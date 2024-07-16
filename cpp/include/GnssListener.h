#ifndef __GNSS_LISTENER_H__
#define __GNSS_LISTENER_H__

#include <string_view>
#include <thread>
#include <functional>
#include <sys/epoll.h>

#include "Constants.h"
#include "GnssEventHandler.h"

namespace gnss::impl{

    using namespace std;

    class GnssListener {
        public:
            using GnssCallback = function<void(const GnssEvent&)>;

            GnssListener() = delete;
            virtual ~GnssListener();

            GnssListener(const string_view gnssPath, const GnssCallback cb, const int& bufSize = DEFAULT_BUFF_SIZE, const int& maxEvents = DEFAULT_MAX_EVENT_CNT);

            void start();
            void stop();
            void setPath(const string_view newPath);
            void setCallback(const GnssCallback cb);
            void setBufSize(const int& size);
            void setMaxEvents(const int& eventCnt);

        private:
            string_view mGnssPath;
            int mGnssFd;
            int mBufferSize;
            int mMaxEvents;
            GnssCallback mCallback;
            // TODO: Should timeout be configurable?
            int mTimeout{1000};
            bool mIsRunning{false};
            thread mThread;

            void run_();
    };
}


#endif // __GNSS_LISTENER_H__
