#ifndef __NMEA_TYPES_H__
#define __NMEA_TYPES_H__

#include <string_view>
#include <string>
#include <optional>
#include <vector>
#include <cstdint>

namespace gnss::impl{

    using Token = std::string;
    using TokenList = std::vector<Token>;

    enum class TalkerId {
        GB,
        GA,
        GP,
        GL
    };

    enum class MessageType {
        GGA,
        GLL,
        GSA,
        GSV,
        RMC,
        VTG
    };

    enum class FixMode {
        INVALID,                  /* Fix not Valid */
        SPS,                      /* Fix Valid, SPS Mode */
        DGPS,
        UNSUPPORTED,
        DEAD_RECKONING,
    };

    struct Timestamp {
        int hour;
        int minute;
        double second;
    };

    struct Date {
            int year;
            int month;
            int day;
    };

    enum NmeaMode {
        AUTONOMOUS,
        DGPS,
        DR,
    };

    struct NmeaData {
        TalkerId talker_id;
        MessageType message_type;
        int checksum;
        TokenList token_list;
        NmeaData() = default;
        virtual ~NmeaData() = default;
    };

    struct RmcData : public NmeaData {
        bool is_valid;
        double longitude;
        double latitude;


        /**
         * Speed over ground, which originally is in knots (unit).
         * It should be converted to Km/h.
         */
        double velocity_kmh;

        /**
         * Bearing from the true north in degrees.
         * Indicates the device's absolute direction.
         * Range: [0-360)
         */
        double course_deg;

        Date date;

        /**
         * Difference between the true north and magnetic north.
         * Range: [0-360)
         */
        double mag_variation;

        NmeaMode mode;
    };

    struct VtgData : public NmeaData {
        /**
         * Bearing from the true north in degrees.
         * Range: [0-360)
         */
        double true_course_deg;

        /**
         * Bearing from the magnetic north in degrees.
         * Range: [0-360)
         */
        double mag_course_deg;

        double speed;

        Date date;

        /**
         * Difference between the true north and magnetic north.
         * Range: [0-360)
         */
        double mag_variation;

        NmeaMode mode;
    };

    struct Coordinates {
        double latitude;
        double longitude;
    };

    struct GgaData : public NmeaData {
        Timestamp utc;
        Coordinates coordinates;
        FixMode mode;

        /**
         * Number of Satellites Used
         * Range: [0-12]
         */
        uint8_t activ_sat_cnt;
        
        /*
         * HDOP
         * Unit: meters
         */
        double hdop;

        /*
         * Altitude above mean sea level
         * Unit: meters
         */
        double altitude_msl;

        /**
         * Geoidal separation (difference between the WGS-84 earth ellipsoid and mean sea level)
         * Thickness from Center of Earth to Surface
         * altitudeMsl + geoidCorr = {Altitude from Ground Up}
         * Unit: meters
         */
        double geoid_corr;

        /**
         * Age of differential GPS data
         * Value: Number or Null if DGPS is unused
         * Unit: seconds
         */
        std::optional<int> diff_corr_age;



    };
}
#endif // __NMEA_TYPES_H__
