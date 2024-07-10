#ifndef __NMEA_PARSER_H__
#define __NMEA_PARSER_H__

#include <memory>
#include <vector>
#include <string_view>
#include "NmeaTypes.h"

namespace gnss::impl {
    using namespace std;
    class NmeaParser {
        public:
            unique_ptr<NmeaData> parse(string_view msg);

        private:
            unique_ptr<NmeaData> _get_common(const TokenList&);
            TokenList _tokenize(const string_view msg);
            bool _verify_checksum(const TokenList& token_list);
            bool _verify_msg_id(const Token& msg_id);
            bool _verify_talker_id(const Token& talker_id);
            bool _verify_all(const TokenList& token_list);
            unique_ptr<GgaData> _parse_gga(unique_ptr<NmeaData> common);
    };

}

#endif // __NMEA_PARSER_H__
