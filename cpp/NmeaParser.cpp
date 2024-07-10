#include "include/NmeaParser.h"

namespace gnss::impl {
    unique_ptr<NmeaData> NmeaParser::parse(string_view msg) {
        auto token_list { _tokenize(msg) };
        auto data { _get_common(token_list) };
        switch (data->message_id) {
            case MessageId::GGA:
                return _parse_gga(data);
                break;


        }

    }

    unique_ptr<GgaData> NmeaParser::_parse_gga(unique_ptr<NmeaData> common) {
        shared_ptr<GgaData> gga { make_unique<GgaData> };
        common->swap(gga);


    }

}
