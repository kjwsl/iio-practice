#ifndef __NMEA_PARSER_H__
#define __NMEA_PARSER_H__

#include <memory>
#include <string_view>
#include "NmeaTypes.h"
#include "Tokenizer.h"

namespace gnss::impl {
    using namespace std;
    class NmeaParser {
        public:
            unique_ptr<NmeaData> parse             (const string_view msg);
            unique_ptr<NmeaData> get_common        (const TokenList&)       const;
            MessageType          get_msg_type      (const Token& msg_type)  const;
            TalkerId             get_talker_id     (const Token& talker_id) const;
            bool                 verify_checksum   (int checksum);


        private:

            bool _verify_all(const TokenList& token_list);

            unique_ptr<GgaData> _parse_gga(unique_ptr<NmeaData> common) const;
            unique_ptr<GgaData> _parse_gsv(unique_ptr<NmeaData> common) const;
            unique_ptr<GgaData> _parse_gsa(unique_ptr<NmeaData> common) const;
            unique_ptr<GgaData> _parse_vtg(unique_ptr<NmeaData> common) const;
            unique_ptr<GgaData> _parse_rmc(unique_ptr<NmeaData> common) const;

            inline Timestamp _parse_timestamp(const Token& tok) const noexcept;
            inline Coordinates _parse_coordinates(const Token& lat, const Token& lat_direc, const Token& lon, const Token& lon_direc) const;
            inline double _parse_coor(const Token& coor) const noexcept;
            inline FixMode _parse_fixmode(const Token& mode) const;
    };

}

#endif // __NMEA_PARSER_H__
