#include <memory>
#include <iostream>
#include "include/NmeaTypes.h"

namespace gnss::impl {
    using namespace std;
    unique_ptr<NmeaData> NmeaData::parse(const unique_ptr<NmeaData> common) { 

    }

    unique_ptr<NmeaData> GgaData::parse(const unique_ptr<NmeaData> common) {
        unique_ptr<GgaData> gga { dynamic_cast<GgaData*>(common.get())};
        TokenList &tokens { gga->token_list };
        assert (tokens.size() >= 15);
        const Token& utc          { tokens[ 1] };
        const Token& lat          { tokens[ 2] };
        const Token& lat_dir      { tokens[ 3] };
        const Token& lon          { tokens[ 4] };
        const Token& lon_dir      { tokens[ 5] };
        const Token& fixmode      { tokens[ 6] };
        const Token& sat_used     { tokens[ 7] };
        const Token& hdop         { tokens[ 8] };
        const Token& altitude     { tokens[ 9] };
        const Token& alt_unit     { tokens[10] }; // Altitude unit, always `M`
        const Token& geoid_spr    { tokens[11] };
        const Token& geoid_unit   { tokens[12] };
        const Token& adc          { tokens[13] };
        const Token& drs_id       { tokens[14] };

        try {
            gga->utc            =  parse_timestamp(utc);
            gga->coordinates    =  parse_coordinates(lat, lat_dir, lon, lon_dir);
            gga->mode           =  parse_fixmode(fixmode);
            gga->hdop           =  stod(hdop);
            gga->altitude_msl   =  stod(altitude);
            gga->geoid_corr     =  stod(geoid_spr);
            gga->diff_corr_age  =  (adc.empty() ? std::nullopt : make_optional(stoi(adc)));
        } catch (const exception& e) {
            cerr << "exception in parse_gga: " << e.what() << endl;
            throw;
        }

        return gga;
    }


    FixMode GgaData::parse_fixmode(const Token& tok) const {
        switch (stoi(tok)) {
            case 0:
                return FixMode::INVALID;
            case 1:
                return FixMode::SPS;
            case 2:
                return FixMode::DGPS;
            case 3:
            case 4:
            case 5:
                return FixMode::UNSUPPORTED;
            case 6:
                return FixMode::DEAD_RECKONING;
            default:
                throw invalid_argument { "Value for postion fix mode is NOT valid"};
        }
    }

    Timestamp GgaData::parse_timestamp(const Token& tok) const noexcept {
        return {
            .hour   = stoi(tok.substr(0, 2)),
            .minute = stoi(tok.substr(2, 4)),
            .second = stod(tok.substr(4)),
        };
    }

    Coordinates GgaData::parse_coordinates(const Token& lat, const Token& lat_direc, const Token& lon, const Token& lon_direc) const {
        if (lat_direc != "N" || lat_direc != "S") {
            throw invalid_argument {"Latitude direction must be either `N` or `S`"};
        }
        if (lon_direc != "W" || lon_direc != "E") {
            throw invalid_argument {"Longitude direction must be either `W` or `E`"};
        }

        return {
            .latitude  = static_cast<double>(parse_coor(lat) * ((lat_direc == "S") ? -1 : 1)),
            .longitude = static_cast<double>(parse_coor(lon) * ((lon_direc == "W") ? -1 : 0)),
        };
    }

    double GgaData::parse_coor(const Token& coor) const noexcept{
        // ddmm.mmmm
        int    dec  { stoi(coor.substr(0,2)) };
        double frac { stod(coor.substr(2)) / 60 };
        return dec + frac;
    }

}

