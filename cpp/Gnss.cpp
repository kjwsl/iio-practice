#include <utils/Log.h>
#include "include/default/Gnss.h"


#define GNSS_PATH "/dev/ttyAMA0"

namespace aidl::android::hardware::gnss {
    ndk::ScopedAStatus Gnss::setCallback(const std::shared_ptr<IGnssCallback>& callback) {
        if (callback == nullptr) {
            ALOGE("%s: Null callback ignored", __func__);
            return ScopedAStatus::fromExceptionCode(STATUS_INVALID_OPERATION);
        }
        sGnssCallback = callback;

        GnssSystemInfo hwInfo {
            .yearOfHw = 2023,
            .name = "Neo 6M"
        };

        const GnssSignalType signal1 {
            .constellation = GnssConstellationType::GPS,
            .carrierFrequencyHz = 1.57542e9,
            .codeType = CODE_TYPE_C,
        };

        const GnssSignalType signals[] {
            signal1,
        };

        sGnssCallback->setGnssSystemInfoCb(hwInfo);
        sGnssCallback->gnssSetSignalTypeCapabilitiesCb(signals);
    }

    ndk::ScopedAStatus Gnss::start() {
        if (mIsActive) {
            ALOGW("Gnss is already started.");
            return ScopedAStatus::ok();
        }

        GnssListener listener { GNSS_PATH, [this, sGnssCallback](const GnssEvent& event) {
            sGnssCallback->nmeaCb(event.timeMs, event.sentence);
            auto res { parser.parse(event) };
            if (res->msgType == "GGA" || res->msgType == "RMC" || res->msgType == "GLL") {
                updateLocation(reinterpret_cast<NmeaLocation>(res));
            } else if (res->msgType == "GSV")  {
                updateSvStatus(reinterpret_cast<NmeaSvStatus>(res));
            } else if (res->msgType == "GSA")  { 
                updateActiveSat(reinterpret_cast<NmeaActiveSat>(res));
            }
        }};
        return ScopedAStatus::ok();
    }

    void updateLocation(const NmeaLocation* loc) {
        if (loc == nullptr) {
            ALOGE("%s: NmeaLocation is null", __func__);
            return;
        }

    }

    struct NmeaLocation {
        UTC time;
        double latitude;
        double longitude;


    }
}
