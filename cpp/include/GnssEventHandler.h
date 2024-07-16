#ifndef __GNSS_EVENT_HANDLER_H__
#define __GNSS_EVENT_HANDLER_H__

#include <cstdint>
#include <string>
#include <stdexcept>
#include <chrono>
#include <optional>

namespace gnss::impl {
    using namespace std;

    struct GnssEvent {
        uint64_t timeMs {};
        string sentence {};

        GnssEvent() = default;
        GnssEvent(const GnssEvent& other) : GnssEvent(other.sentence, other.timeMs) {}
        GnssEvent(const string_view buffer, const uint64_t& timeMs) : sentence(buffer), timeMs(timeMs) {}
    };

    class GnssEventHandler {
        private:
            GnssEvent mEvent;
            inline uint64_t getCurrentTimeMs_() {
                using namespace chrono;
                return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            };

        public:
            GnssEventHandler() = default;
            virtual ~GnssEventHandler() = default;

            string_view getBuffer() { return mEvent.sentence; }
            void writeToBuffer(const string_view str) {
                if (str.size() > mEvent.sentence.size()) {
                    throw runtime_error { "Buffer size is not big enough to hold the string" };
                }

                mEvent.sentence += str;
                mEvent.timeMs = getCurrentTimeMs_();
            }

            const std::optional<GnssEvent> extractNmeaSentence() noexcept{
                if (!hasNextNmeaSentence()) {
                    startAnew();
                    return std::nullopt;
                }

                auto pos { mEvent.sentence.find("\n")};

                string_view buf { mEvent.sentence.substr(0, pos)};
                mEvent.sentence.erase(0, pos);

                return GnssEvent{buf, getCurrentTimeMs_()};
            }

            /**
             * Throw away buffer until the character `$`
             */
            void startAnew() {
                auto pos {mEvent.sentence.find("$")};
                if (pos == string::npos) {
                    pos = mEvent.sentence.find("\n");
                    if (pos == string::npos) {
                        mEvent.sentence.clear();
                        return;
                    } 
                    pos++;
                } 
                mEvent.sentence = mEvent.sentence.substr(pos);
            }

            bool hasNextNmeaSentence() {
                return (mEvent.sentence.front() == '$' && mEvent.sentence.back() == '\n');
            }


            void clear() {
                mEvent.sentence.clear();
                mEvent.timeMs = 0;
            }
    };

};


#endif// __GNSS_EVENT_HANDLER_H__