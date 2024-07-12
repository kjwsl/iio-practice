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
            m_tokenizer_ptr->set_source(msg);
            auto token_list { m_tokenizer_ptr->tokenize() };
            auto data { _get_common(token_list) };
            switch (data->message_type) {
                case MessageType::GGA:
                    return make_unique<GgaData>(move(data));
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




}
