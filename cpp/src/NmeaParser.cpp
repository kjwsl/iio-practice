#include <cassert>
#include <stdexcept>
#include <string>
#include <iostream>
#include <cstring>

#include "include/NmeaParser.h"

namespace gnss::impl {
    unique_ptr<NmeaData> NmeaParser::parse(const string_view msg) {
        if (msg.empty()){
            throw invalid_argument {"Empty NMEA sentence"};
        }

        try {
            auto token_list { _tokenize(msg) };
            auto data { _get_common(token_list) };
            switch (data->message_type) {
                case MessageType::GGA:
                    return _parse_gga(std::move(data));
                    break;
                /** TODO:
                case MessageType::GSA:
                    return _parse_gsa(std::move(data));
                    break;
                case MessageType::GLL:
                    return _parse_gga(std::move(data));
                    break;
                case MessageType::GSV:
                    return _parse_gga(std::move(data));
                    break;
                case MessageType::RMC:
                    return _parse_gga(std::move(data));
                    break;
                case MessageType::VTG:
                    return _parse_gga(std::move(data));
                    break;
                    */
                default:
                    throw runtime_error {"Invalid message id"};
            }
        } catch (const exception& e) {
            cerr << "Exception in parse(): " << e.what() << endl;
            throw;
        }

    }

    TokenList NmeaParser::_tokenize(const string_view msg) {
        TokenList list;
        size_t pos{};
        size_t new_pos;
        while((new_pos = msg.find(",", pos)) != string::npos){
            cout << "pos:" << pos << "new_pos: " << new_pos << endl;
            list.emplace_back(msg.substr(pos, new_pos - pos).data());
            pos = new_pos + 1;
        }

        for (auto it = list.begin(); it != list.end(); it++) {
            cout << it->data() << endl;
        }
        return list;
    }

    


    unique_ptr<NmeaData> NmeaParser::_get_common(const TokenList& tlist) const {
        cout << "get_common()" << endl;
        auto data { make_unique<NmeaData>()};

        try {
            data->token_list = tlist;
            data->checksum = stoi(tlist.back());
            data->talker_id = _get_talker_id(tlist[0].substr(1,2));
            data->message_type = _get_msg_type(tlist[0].substr(3));

        } catch(const exception& e) {
            cout << "exception in get_common(): " << e.what() << endl;
        }
        return data;
    }

    TalkerId NmeaParser::_get_talker_id(const Token& talker_id) const {
        // TODO: Think of a better way, this is O(n) time!
        if      (talker_id == "GA") return TalkerId::GA; 
        else if (talker_id == "GB") return TalkerId::GB;
        else if (talker_id == "GL") return TalkerId::GL;
        else if (talker_id == "GP") return TalkerId::GP;
        else    {
            throw invalid_argument { "Unrecognized talker ID" };
        }
    }

    MessageType NmeaParser::_get_msg_type(const Token& msg_type) const {
        if      (msg_type == "GGA") return MessageType::GGA;
        else if (msg_type == "GLL") return MessageType::GLL;
        else if (msg_type == "GSA") return MessageType::GSA;
        else if (msg_type == "GSV") return MessageType::GSV;
        else {
            throw invalid_argument { "Unrecognized message type" };
        }
    }

    unique_ptr<GgaData> NmeaParser::_parse_gga(unique_ptr<NmeaData> common) const {
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
            gga->utc            =  _parse_timestamp(utc);
            gga->coordinates    =  _parse_coordinates(lat, lat_dir, lon, lon_dir);
            gga->mode           =  _parse_fixmode(fixmode);
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

    FixMode NmeaParser::_parse_fixmode(const Token& tok) const {
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

    Timestamp NmeaParser::_parse_timestamp(const Token& tok) const noexcept {
        return {
            .hour   = stoi(tok.substr(0, 2)),
            .minute = stoi(tok.substr(2, 4)),
            .second = stod(tok.substr(4)),
        };
    }

    Coordinates NmeaParser::_parse_coordinates(const Token& lat, const Token& lat_direc, const Token& lon, const Token& lon_direc) const {
        if (lat_direc != "N" || lat_direc != "S") {
            throw invalid_argument {"Latitude direction must be either `N` or `S`"};
        }
        if (lon_direc != "W" || lon_direc != "E") {
            throw invalid_argument {"Longitude direction must be either `W` or `E`"};
        }

        return {
            .latitude  = static_cast<double>(_parse_coor(lat) * ((lat_direc == "S") ? -1 : 1)),
            .longitude = static_cast<double>(_parse_coor(lon) * ((lon_direc == "W") ? -1 : 0)),
        };
    }

    double NmeaParser::_parse_coor(const Token& coor) const noexcept{
        // ddmm.mmmm
        int    dec  { stoi(coor.substr(0,2)) };
        double frac { stod(coor.substr(2)) / 60 };
        return dec + frac;
    }



}
