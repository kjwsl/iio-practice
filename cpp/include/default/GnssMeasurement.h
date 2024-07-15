/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: out/host/linux-x86/bin/aidl --lang=cpp --structured --version 3 --hash 747fa8b8b4bb55d21f2c42446dd1b31de1dfbeaa -t --stability vintf --min_sdk_version current --ninja -d out/soong/.intermediates/hardware/interfaces/gnss/aidl/android.hardware.gnss-V3-cpp-source/gen/staging/android/hardware/gnss/GnssMeasurement.cpp.d -h out/soong/.intermediates/hardware/interfaces/gnss/aidl/android.hardware.gnss-V3-cpp-source/gen/include/staging -o out/soong/.intermediates/hardware/interfaces/gnss/aidl/android.hardware.gnss-V3-cpp-source/gen/staging -Nhardware/interfaces/gnss/aidl/aidl_api/android.hardware.gnss/3 hardware/interfaces/gnss/aidl/aidl_api/android.hardware.gnss/3/android/hardware/gnss/GnssMeasurement.aidl
 */
#pragma once

#include <android/binder_to_string.h>
#include <android/hardware/gnss/CorrelationVector.h>
#include <android/hardware/gnss/GnssMultipathIndicator.h>
#include <android/hardware/gnss/GnssSignalType.h>
#include <android/hardware/gnss/SatellitePvt.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace android::hardware::gnss {
class CorrelationVector;
class GnssSignalType;
class SatellitePvt;
}  // namespace android::hardware::gnss
namespace android {
namespace hardware {
namespace gnss {
class GnssMeasurement : public ::android::Parcelable {
public:
  int32_t flags = 0;
  int32_t svid = 0;
  ::android::hardware::gnss::GnssSignalType signalType;
  double timeOffsetNs = 0.000000;
  int32_t state = 0;
  int64_t receivedSvTimeInNs = 0L;
  int64_t receivedSvTimeUncertaintyInNs = 0L;
  double antennaCN0DbHz = 0.000000;
  double basebandCN0DbHz = 0.000000;
  double pseudorangeRateMps = 0.000000;
  double pseudorangeRateUncertaintyMps = 0.000000;
  int32_t accumulatedDeltaRangeState = 0;
  double accumulatedDeltaRangeM = 0.000000;
  double accumulatedDeltaRangeUncertaintyM = 0.000000;
  int64_t carrierCycles = 0L;
  double carrierPhase = 0.000000;
  double carrierPhaseUncertainty = 0.000000;
  ::android::hardware::gnss::GnssMultipathIndicator multipathIndicator = ::android::hardware::gnss::GnssMultipathIndicator::UNKNOWN;
  double snrDb = 0.000000;
  double agcLevelDb = 0.000000;
  double fullInterSignalBiasNs = 0.000000;
  double fullInterSignalBiasUncertaintyNs = 0.000000;
  double satelliteInterSignalBiasNs = 0.000000;
  double satelliteInterSignalBiasUncertaintyNs = 0.000000;
  ::android::hardware::gnss::SatellitePvt satellitePvt;
  ::std::vector<::android::hardware::gnss::CorrelationVector> correlationVectors;
  inline bool operator!=(const GnssMeasurement& rhs) const {
    return std::tie(flags, svid, signalType, timeOffsetNs, state, receivedSvTimeInNs, receivedSvTimeUncertaintyInNs, antennaCN0DbHz, basebandCN0DbHz, pseudorangeRateMps, pseudorangeRateUncertaintyMps, accumulatedDeltaRangeState, accumulatedDeltaRangeM, accumulatedDeltaRangeUncertaintyM, carrierCycles, carrierPhase, carrierPhaseUncertainty, multipathIndicator, snrDb, agcLevelDb, fullInterSignalBiasNs, fullInterSignalBiasUncertaintyNs, satelliteInterSignalBiasNs, satelliteInterSignalBiasUncertaintyNs, satellitePvt, correlationVectors) != std::tie(rhs.flags, rhs.svid, rhs.signalType, rhs.timeOffsetNs, rhs.state, rhs.receivedSvTimeInNs, rhs.receivedSvTimeUncertaintyInNs, rhs.antennaCN0DbHz, rhs.basebandCN0DbHz, rhs.pseudorangeRateMps, rhs.pseudorangeRateUncertaintyMps, rhs.accumulatedDeltaRangeState, rhs.accumulatedDeltaRangeM, rhs.accumulatedDeltaRangeUncertaintyM, rhs.carrierCycles, rhs.carrierPhase, rhs.carrierPhaseUncertainty, rhs.multipathIndicator, rhs.snrDb, rhs.agcLevelDb, rhs.fullInterSignalBiasNs, rhs.fullInterSignalBiasUncertaintyNs, rhs.satelliteInterSignalBiasNs, rhs.satelliteInterSignalBiasUncertaintyNs, rhs.satellitePvt, rhs.correlationVectors);
  }
  inline bool operator<(const GnssMeasurement& rhs) const {
    return std::tie(flags, svid, signalType, timeOffsetNs, state, receivedSvTimeInNs, receivedSvTimeUncertaintyInNs, antennaCN0DbHz, basebandCN0DbHz, pseudorangeRateMps, pseudorangeRateUncertaintyMps, accumulatedDeltaRangeState, accumulatedDeltaRangeM, accumulatedDeltaRangeUncertaintyM, carrierCycles, carrierPhase, carrierPhaseUncertainty, multipathIndicator, snrDb, agcLevelDb, fullInterSignalBiasNs, fullInterSignalBiasUncertaintyNs, satelliteInterSignalBiasNs, satelliteInterSignalBiasUncertaintyNs, satellitePvt, correlationVectors) < std::tie(rhs.flags, rhs.svid, rhs.signalType, rhs.timeOffsetNs, rhs.state, rhs.receivedSvTimeInNs, rhs.receivedSvTimeUncertaintyInNs, rhs.antennaCN0DbHz, rhs.basebandCN0DbHz, rhs.pseudorangeRateMps, rhs.pseudorangeRateUncertaintyMps, rhs.accumulatedDeltaRangeState, rhs.accumulatedDeltaRangeM, rhs.accumulatedDeltaRangeUncertaintyM, rhs.carrierCycles, rhs.carrierPhase, rhs.carrierPhaseUncertainty, rhs.multipathIndicator, rhs.snrDb, rhs.agcLevelDb, rhs.fullInterSignalBiasNs, rhs.fullInterSignalBiasUncertaintyNs, rhs.satelliteInterSignalBiasNs, rhs.satelliteInterSignalBiasUncertaintyNs, rhs.satellitePvt, rhs.correlationVectors);
  }
  inline bool operator<=(const GnssMeasurement& rhs) const {
    return std::tie(flags, svid, signalType, timeOffsetNs, state, receivedSvTimeInNs, receivedSvTimeUncertaintyInNs, antennaCN0DbHz, basebandCN0DbHz, pseudorangeRateMps, pseudorangeRateUncertaintyMps, accumulatedDeltaRangeState, accumulatedDeltaRangeM, accumulatedDeltaRangeUncertaintyM, carrierCycles, carrierPhase, carrierPhaseUncertainty, multipathIndicator, snrDb, agcLevelDb, fullInterSignalBiasNs, fullInterSignalBiasUncertaintyNs, satelliteInterSignalBiasNs, satelliteInterSignalBiasUncertaintyNs, satellitePvt, correlationVectors) <= std::tie(rhs.flags, rhs.svid, rhs.signalType, rhs.timeOffsetNs, rhs.state, rhs.receivedSvTimeInNs, rhs.receivedSvTimeUncertaintyInNs, rhs.antennaCN0DbHz, rhs.basebandCN0DbHz, rhs.pseudorangeRateMps, rhs.pseudorangeRateUncertaintyMps, rhs.accumulatedDeltaRangeState, rhs.accumulatedDeltaRangeM, rhs.accumulatedDeltaRangeUncertaintyM, rhs.carrierCycles, rhs.carrierPhase, rhs.carrierPhaseUncertainty, rhs.multipathIndicator, rhs.snrDb, rhs.agcLevelDb, rhs.fullInterSignalBiasNs, rhs.fullInterSignalBiasUncertaintyNs, rhs.satelliteInterSignalBiasNs, rhs.satelliteInterSignalBiasUncertaintyNs, rhs.satellitePvt, rhs.correlationVectors);
  }
  inline bool operator==(const GnssMeasurement& rhs) const {
    return std::tie(flags, svid, signalType, timeOffsetNs, state, receivedSvTimeInNs, receivedSvTimeUncertaintyInNs, antennaCN0DbHz, basebandCN0DbHz, pseudorangeRateMps, pseudorangeRateUncertaintyMps, accumulatedDeltaRangeState, accumulatedDeltaRangeM, accumulatedDeltaRangeUncertaintyM, carrierCycles, carrierPhase, carrierPhaseUncertainty, multipathIndicator, snrDb, agcLevelDb, fullInterSignalBiasNs, fullInterSignalBiasUncertaintyNs, satelliteInterSignalBiasNs, satelliteInterSignalBiasUncertaintyNs, satellitePvt, correlationVectors) == std::tie(rhs.flags, rhs.svid, rhs.signalType, rhs.timeOffsetNs, rhs.state, rhs.receivedSvTimeInNs, rhs.receivedSvTimeUncertaintyInNs, rhs.antennaCN0DbHz, rhs.basebandCN0DbHz, rhs.pseudorangeRateMps, rhs.pseudorangeRateUncertaintyMps, rhs.accumulatedDeltaRangeState, rhs.accumulatedDeltaRangeM, rhs.accumulatedDeltaRangeUncertaintyM, rhs.carrierCycles, rhs.carrierPhase, rhs.carrierPhaseUncertainty, rhs.multipathIndicator, rhs.snrDb, rhs.agcLevelDb, rhs.fullInterSignalBiasNs, rhs.fullInterSignalBiasUncertaintyNs, rhs.satelliteInterSignalBiasNs, rhs.satelliteInterSignalBiasUncertaintyNs, rhs.satellitePvt, rhs.correlationVectors);
  }
  inline bool operator>(const GnssMeasurement& rhs) const {
    return std::tie(flags, svid, signalType, timeOffsetNs, state, receivedSvTimeInNs, receivedSvTimeUncertaintyInNs, antennaCN0DbHz, basebandCN0DbHz, pseudorangeRateMps, pseudorangeRateUncertaintyMps, accumulatedDeltaRangeState, accumulatedDeltaRangeM, accumulatedDeltaRangeUncertaintyM, carrierCycles, carrierPhase, carrierPhaseUncertainty, multipathIndicator, snrDb, agcLevelDb, fullInterSignalBiasNs, fullInterSignalBiasUncertaintyNs, satelliteInterSignalBiasNs, satelliteInterSignalBiasUncertaintyNs, satellitePvt, correlationVectors) > std::tie(rhs.flags, rhs.svid, rhs.signalType, rhs.timeOffsetNs, rhs.state, rhs.receivedSvTimeInNs, rhs.receivedSvTimeUncertaintyInNs, rhs.antennaCN0DbHz, rhs.basebandCN0DbHz, rhs.pseudorangeRateMps, rhs.pseudorangeRateUncertaintyMps, rhs.accumulatedDeltaRangeState, rhs.accumulatedDeltaRangeM, rhs.accumulatedDeltaRangeUncertaintyM, rhs.carrierCycles, rhs.carrierPhase, rhs.carrierPhaseUncertainty, rhs.multipathIndicator, rhs.snrDb, rhs.agcLevelDb, rhs.fullInterSignalBiasNs, rhs.fullInterSignalBiasUncertaintyNs, rhs.satelliteInterSignalBiasNs, rhs.satelliteInterSignalBiasUncertaintyNs, rhs.satellitePvt, rhs.correlationVectors);
  }
  inline bool operator>=(const GnssMeasurement& rhs) const {
    return std::tie(flags, svid, signalType, timeOffsetNs, state, receivedSvTimeInNs, receivedSvTimeUncertaintyInNs, antennaCN0DbHz, basebandCN0DbHz, pseudorangeRateMps, pseudorangeRateUncertaintyMps, accumulatedDeltaRangeState, accumulatedDeltaRangeM, accumulatedDeltaRangeUncertaintyM, carrierCycles, carrierPhase, carrierPhaseUncertainty, multipathIndicator, snrDb, agcLevelDb, fullInterSignalBiasNs, fullInterSignalBiasUncertaintyNs, satelliteInterSignalBiasNs, satelliteInterSignalBiasUncertaintyNs, satellitePvt, correlationVectors) >= std::tie(rhs.flags, rhs.svid, rhs.signalType, rhs.timeOffsetNs, rhs.state, rhs.receivedSvTimeInNs, rhs.receivedSvTimeUncertaintyInNs, rhs.antennaCN0DbHz, rhs.basebandCN0DbHz, rhs.pseudorangeRateMps, rhs.pseudorangeRateUncertaintyMps, rhs.accumulatedDeltaRangeState, rhs.accumulatedDeltaRangeM, rhs.accumulatedDeltaRangeUncertaintyM, rhs.carrierCycles, rhs.carrierPhase, rhs.carrierPhaseUncertainty, rhs.multipathIndicator, rhs.snrDb, rhs.agcLevelDb, rhs.fullInterSignalBiasNs, rhs.fullInterSignalBiasUncertaintyNs, rhs.satelliteInterSignalBiasNs, rhs.satelliteInterSignalBiasUncertaintyNs, rhs.satellitePvt, rhs.correlationVectors);
  }

  enum : int32_t { HAS_SNR = 1 };
  enum : int32_t { HAS_CARRIER_FREQUENCY = 512 };
  enum : int32_t { HAS_CARRIER_CYCLES = 1024 };
  enum : int32_t { HAS_CARRIER_PHASE = 2048 };
  enum : int32_t { HAS_CARRIER_PHASE_UNCERTAINTY = 4096 };
  enum : int32_t { HAS_AUTOMATIC_GAIN_CONTROL = 8192 };
  enum : int32_t { HAS_FULL_ISB = 65536 };
  enum : int32_t { HAS_FULL_ISB_UNCERTAINTY = 131072 };
  enum : int32_t { HAS_SATELLITE_ISB = 262144 };
  enum : int32_t { HAS_SATELLITE_ISB_UNCERTAINTY = 524288 };
  enum : int32_t { HAS_SATELLITE_PVT = 1048576 };
  enum : int32_t { HAS_CORRELATION_VECTOR = 2097152 };
  enum : int32_t { STATE_UNKNOWN = 0 };
  enum : int32_t { STATE_CODE_LOCK = 1 };
  enum : int32_t { STATE_BIT_SYNC = 2 };
  enum : int32_t { STATE_SUBFRAME_SYNC = 4 };
  enum : int32_t { STATE_TOW_DECODED = 8 };
  enum : int32_t { STATE_MSEC_AMBIGUOUS = 16 };
  enum : int32_t { STATE_SYMBOL_SYNC = 32 };
  enum : int32_t { STATE_GLO_STRING_SYNC = 64 };
  enum : int32_t { STATE_GLO_TOD_DECODED = 128 };
  enum : int32_t { STATE_BDS_D2_BIT_SYNC = 256 };
  enum : int32_t { STATE_BDS_D2_SUBFRAME_SYNC = 512 };
  enum : int32_t { STATE_GAL_E1BC_CODE_LOCK = 1024 };
  enum : int32_t { STATE_GAL_E1C_2ND_CODE_LOCK = 2048 };
  enum : int32_t { STATE_GAL_E1B_PAGE_SYNC = 4096 };
  enum : int32_t { STATE_SBAS_SYNC = 8192 };
  enum : int32_t { STATE_TOW_KNOWN = 16384 };
  enum : int32_t { STATE_GLO_TOD_KNOWN = 32768 };
  enum : int32_t { STATE_2ND_CODE_LOCK = 65536 };
  enum : int32_t { ADR_STATE_UNKNOWN = 0 };
  enum : int32_t { ADR_STATE_VALID = 1 };
  enum : int32_t { ADR_STATE_RESET = 2 };
  enum : int32_t { ADR_STATE_CYCLE_SLIP = 4 };
  enum : int32_t { ADR_STATE_HALF_CYCLE_RESOLVED = 8 };
  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCRIPTOR (u"android.hardware.gnss.GnssMeasurement");
    return DESCRIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream _aidl_os;
    _aidl_os << "GnssMeasurement{";
    _aidl_os << "flags: " << ::android::internal::ToString(flags);
    _aidl_os << ", svid: " << ::android::internal::ToString(svid);
    _aidl_os << ", signalType: " << ::android::internal::ToString(signalType);
    _aidl_os << ", timeOffsetNs: " << ::android::internal::ToString(timeOffsetNs);
    _aidl_os << ", state: " << ::android::internal::ToString(state);
    _aidl_os << ", receivedSvTimeInNs: " << ::android::internal::ToString(receivedSvTimeInNs);
    _aidl_os << ", receivedSvTimeUncertaintyInNs: " << ::android::internal::ToString(receivedSvTimeUncertaintyInNs);
    _aidl_os << ", antennaCN0DbHz: " << ::android::internal::ToString(antennaCN0DbHz);
    _aidl_os << ", basebandCN0DbHz: " << ::android::internal::ToString(basebandCN0DbHz);
    _aidl_os << ", pseudorangeRateMps: " << ::android::internal::ToString(pseudorangeRateMps);
    _aidl_os << ", pseudorangeRateUncertaintyMps: " << ::android::internal::ToString(pseudorangeRateUncertaintyMps);
    _aidl_os << ", accumulatedDeltaRangeState: " << ::android::internal::ToString(accumulatedDeltaRangeState);
    _aidl_os << ", accumulatedDeltaRangeM: " << ::android::internal::ToString(accumulatedDeltaRangeM);
    _aidl_os << ", accumulatedDeltaRangeUncertaintyM: " << ::android::internal::ToString(accumulatedDeltaRangeUncertaintyM);
    _aidl_os << ", carrierCycles: " << ::android::internal::ToString(carrierCycles);
    _aidl_os << ", carrierPhase: " << ::android::internal::ToString(carrierPhase);
    _aidl_os << ", carrierPhaseUncertainty: " << ::android::internal::ToString(carrierPhaseUncertainty);
    _aidl_os << ", multipathIndicator: " << ::android::internal::ToString(multipathIndicator);
    _aidl_os << ", snrDb: " << ::android::internal::ToString(snrDb);
    _aidl_os << ", agcLevelDb: " << ::android::internal::ToString(agcLevelDb);
    _aidl_os << ", fullInterSignalBiasNs: " << ::android::internal::ToString(fullInterSignalBiasNs);
    _aidl_os << ", fullInterSignalBiasUncertaintyNs: " << ::android::internal::ToString(fullInterSignalBiasUncertaintyNs);
    _aidl_os << ", satelliteInterSignalBiasNs: " << ::android::internal::ToString(satelliteInterSignalBiasNs);
    _aidl_os << ", satelliteInterSignalBiasUncertaintyNs: " << ::android::internal::ToString(satelliteInterSignalBiasUncertaintyNs);
    _aidl_os << ", satellitePvt: " << ::android::internal::ToString(satellitePvt);
    _aidl_os << ", correlationVectors: " << ::android::internal::ToString(correlationVectors);
    _aidl_os << "}";
    return _aidl_os.str();
  }
};  // class GnssMeasurement
}  // namespace gnss
}  // namespace hardware
}  // namespace android
