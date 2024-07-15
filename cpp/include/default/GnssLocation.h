/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: out/host/linux-x86/bin/aidl --lang=cpp --structured --version 3 --hash 747fa8b8b4bb55d21f2c42446dd1b31de1dfbeaa -t --stability vintf --min_sdk_version current --ninja -d out/soong/.intermediates/hardware/interfaces/gnss/aidl/android.hardware.gnss-V3-cpp-source/gen/staging/android/hardware/gnss/GnssLocation.cpp.d -h out/soong/.intermediates/hardware/interfaces/gnss/aidl/android.hardware.gnss-V3-cpp-source/gen/include/staging -o out/soong/.intermediates/hardware/interfaces/gnss/aidl/android.hardware.gnss-V3-cpp-source/gen/staging -Nhardware/interfaces/gnss/aidl/aidl_api/android.hardware.gnss/3 hardware/interfaces/gnss/aidl/aidl_api/android.hardware.gnss/3/android/hardware/gnss/GnssLocation.aidl
 */
#pragma once

#include <android/binder_to_string.h>
#include <android/hardware/gnss/ElapsedRealtime.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace android::hardware::gnss {
class ElapsedRealtime;
}  // namespace android::hardware::gnss
namespace android {
namespace hardware {
namespace gnss {
class GnssLocation : public ::android::Parcelable {
public:
  int32_t gnssLocationFlags = 0;
  double latitudeDegrees = 0.000000;
  double longitudeDegrees = 0.000000;
  double altitudeMeters = 0.000000;
  double speedMetersPerSec = 0.000000;
  double bearingDegrees = 0.000000;
  double horizontalAccuracyMeters = 0.000000;
  double verticalAccuracyMeters = 0.000000;
  double speedAccuracyMetersPerSecond = 0.000000;
  double bearingAccuracyDegrees = 0.000000;
  int64_t timestampMillis = 0L;
  // ::android::hardware::gnss::ElapsedRealtime elapsedRealtime;
  enum : int32_t { HAS_LAT_LONG = 1 };
  enum : int32_t { HAS_ALTITUDE = 2 };
  enum : int32_t { HAS_SPEED = 4 };
  enum : int32_t { HAS_BEARING = 8 };
  enum : int32_t { HAS_HORIZONTAL_ACCURACY = 16 };
  enum : int32_t { HAS_VERTICAL_ACCURACY = 32 };
  enum : int32_t { HAS_SPEED_ACCURACY = 64 };
  enum : int32_t { HAS_BEARING_ACCURACY = 128 };
};  // class GnssLocation
}  // namespace gnss
}  // namespace hardware
}  // namespace android
