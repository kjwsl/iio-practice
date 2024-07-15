#include <iostream>
#include <cassert>
#include <string>
#include <cstring>
#include <optional>
#include <regex>
#include <chrono>


#include "include/default/GnssLocation.h"
#include "include/default/GnssMeasurement.h"

using namespace std;
using namespace android::hardware::gnss;

const std::string& kSample{
    "$GPGGA,092750.000,5321.6802,N,00630.3372,W,1,8,1.03,61.7,M,55.2,M,,*76\n"
    "$GPGSA,A,3,10,07,05,02,29,04,08,13,,,,,1.72,1.03,1.38*0A\n"
    "$GPGSV,3,1,11,10,63,137,17,07,61,098,15,05,59,290,20,08,54,157,30*70\n"
    "$GPGSV,3,2,11,02,39,223,19,13,28,070,17,26,23,252,,04,14,186,14*79\n"
    "$GPGSV,3,3,11,29,09,301,24,16,09,020,,36,,,*76\n"
    "$GPRMC,092750.000,A,5321.6802,N,00630.3372,W,0.02,31.66,280511,,,A*43\n"
    "$GPVTG,224.592,T,224.592,M,0.003,N,0.005,K,D*20\n"
    "$GPGGA,092751.000,5321.6802,N,00630.3371,W,1,8,1.03,61.7,M,55.3,M,,*75\n"
    "$GPGSA,A,3,10,07,05,02,29,04,08,13,,,,,1.72,1.03,1.38*0A\n"
    "$GPGSV,3,1,11,10,63,137,17,07,61,098,15,05,59,290,20,08,54,157,30*70\n"
    "$GPGSV,3,2,11,02,39,223,16,13,28,070,17,26,23,252,,04,14,186,15*77\n"
    "$GPGSV,3,3,11,29,09,301,24,16,09,020,,36,,,*76\n"
    "$GNVTG,139.969,T,139.969,M,0.007,N,0.013,K,D*3D\n"
    "$GPRMC,092751.000,A,5321.6802,N,00630.3371,W,0.06,31.66,280511,,,A*45\n"
    "$GBRMC,092751.000,A,5321.6802,N,00630.3371,W,0.06,31.66,280511,,,A*45\n"
    "$GPGLL,5109.0262317,N,11401.8407304,W,202725.00,A,D*79\n"
    "$GNGLL,5109.0262321,S,11401.8407167,E,174738.00,V,E*6B\n"
    "$GPVTG,309.62,T,,M,0.13,N,0.2,K,A*23\n"

};

struct NmeaData {
    vector<string> tokens;
    string msg;
    string talker_id;
    string msg_type;
    int checksum;
};

void print_match(string src, const regex& re, const string_view title = "") {
    if (!title.empty()) {
        cout << "#####################################" << endl;
        cout << title << endl;
        cout << "#####################################" << endl;
    }
    int i = 1;
    smatch match{};

    while (regex_search(src, match, re)) {
        cout << i++ << ": " << "\n";
        cout << "\tMatch: " << match.str() << "\n";
        for (int j = 1; j < match.size(); j++) {
            cout << "\tCapture(" << j << "): " << match[j].str() << "\n";
        }
        src = match.suffix().str();
    } 
}


optional<vector<vector<string>>> get_regex_matches(const string& src, const regex& re) {
    string text{src};
    smatch matches{};
    vector<vector<string>> ret;
    
    while (regex_search(text, matches, re)) {
        vector<string> tmp {};
        for (const auto& match : matches) {
            tmp.emplace_back(match.str());
        }
        if (tmp.empty()) {
            return nullopt;
        }
        ret.emplace_back(tmp);
        text = matches.suffix().str();
    }

    if (!ret.empty()){
        return ret;
    }

    return nullopt;
}

optional<vector<string>> get_regex_match(const string& src, const regex& re) {
    string text{src};
    smatch matches{};
    vector<string> ret;
    
    if (regex_search(text, matches, re)) {
        for (const auto& match : matches) {
            ret.emplace_back(match.str());
        }
        return ret;
    }
    return nullopt;
}



void parse_gsa(const string& sentence) {
    assert(!sentence.empty());
    static const regex re_gsa {R"(([AM]),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*)(?:,(\d+\.\d+)){3})"};

    const auto& matches { get_regex_match(sentence, re_gsa) };
    if (matches->empty() || matches->size() < 17) {
        return;
    }
    const auto& match_values { *std::move(matches) };


    
    gnss::impl::NmeaMode1 mode1;
    gnss::impl::NmeaMode2 mode2;
    if (match_values[0] == "M") {
        mode1 = gnss::impl::NmeaMode1::M;
    } else {
        mode1 = gnss::impl::NmeaMode1::A;
    }

    if (match_values[1] == "")

    const string& mode2 { match_values[1] };
    const string& pdop { match_values[14] };
    const string& hdop { match_values[15] };
    const string& vdop { match_values[16] };

    const int satellites[12] {
        stoi(match_values[2]),
        stoi(match_values[3]),
        stoi(match_values[4]),
        stoi(match_values[5]),
        stoi(match_values[6]),
        stoi(match_values[7]),
        stoi(match_values[8]),
        stoi(match_values[9]),
        stoi(match_values[10]),
        stoi(match_values[11]),
        stoi(match_values[12]),
        stoi(match_values[13]),
    };
};

optional<GnssLocation> parse_gga(const string& src) {
    static const regex re_gga {R"((\d{2})(\d{2})(\d*\.\d*),(\d{2}\d*\.\d*),([NS]),(\d{3}\d*\.\d*),([EW]),([1-4]),(\d{0,2}),(\d*\.\d*),(\d*\.\d*),([M]),(\d*\.\d*),([M]),(\d*\.\d*)?,(\d*))"};
    const auto& matches {get_regex_match(src, re_gga)};
    if (matches->empty()) {
        return nullopt;
    }
    const auto& match_vals {*std::move(matches)};
    
    GnssLocation loc {
        .gnssLocationFlags = GnssLocation::HAS_BEARING | GnssLocation::HAS_LAT_LONG | GnssLocation::HAS_ALTITUDE,
        .latitudeDegrees = (stoi(match_vals[3]) + stod(match_vals[4])/60)*(match_vals[5] == "S" ? -1 : 1),
        .longitudeDegrees = (stoi(match_vals[6]) + stod(match_vals[7])/60)*(match_vals[8] == "W" ? -1 : 1),
        .altitudeMeters = stod(match_vals[12])+stod(match_vals[14]),
        .horizontalAccuracyMeters = 2.5 * stod(match_vals[11]), // TODO: 2.5 is the baseline accuracy of the sensor (neo6m), make it generic
        .timestampMillis = static_cast<int64_t>((stoi(match_vals[0])*3600 + stoi(match_vals[1])*60 + stod(match_vals[2]))*1000),

    };

    return loc;

}

optional<vector<vector<string>>> parse_common(const string& src) {
    static const regex re_common {R"(\$(GP|GB|GA|GL|GN|GI)(GSA|GGA|VTG|RMC|GLL|GSV),(.*)\*([\dA-E]{2})\n)"};

    return get_regex_matches(src,re_common);
}

void parse(const string& str) {
    const auto& sentences { parse_common(str) };
    if (sentences->empty()) {
        return;
    }
    for (int i = 0; i < sentences->size(); i++) {
        const auto& sentence { sentences->at(i)};
        const string& talker { sentence[1] };
        const string& msg_type { sentence[2] };
        const string& rest { sentence[3] };
        const string& checksum { sentence[4] };
        if (msg_type.empty()) {
            throw invalid_argument { "Message type is empty"};
        }
        if (msg_type == "GSA") {
            parse_gsa(rest);
        } else if (msg_type == "GGA") {
            parse_gga(rest);
        }


        cout << "(" << i + 1 << "):\n";
        for (const auto& field : sentence) {
            cout << "\tCapture:" << field << endl;
        }
    }

}


int main() {
    const string re_gsv {R"(GSV,(\d),(\d),(\d{2})((?:,\d{0,2}?,\d{0,2}?,\d{0,3}?,\d{0,2}?)*))"};
    const string re_gsa {R"(GSA,(\w),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*)(?:,(\d+\.\d+)){3})"};
    const string re_rmc {R"(RMC,(\d{2})(\d{2})(\d{2}\.\d{3}),([AV]),(\d{2})(\d{2}\.\d{4}),([NS]),(\d{3})(\d{2}\.\d{4}),([EW]),(\d*\.\d*),(\d*\.\d*),(\d{2})(\d{2})(\d{2}),([EW]?),(E?),([ADE]))"};
    const string re_gll {R"(GLL,(\d{2})(\d{2}\.\d*),([NS]),(\d{3})(\d*\.\d*),([EW]),(\d{2})(\d{2})(\d*\.\d*),([AV]),([ADE]))"};
    const string re_vtg {R"(VTG,(\d*\.\d*)?,([TM]),(\d*\.\d*)?,([TM]),(\d*\.\d*),([NK]),(\d*\.\d*),([NK]),([ADE]))"};

    auto now { chrono::system_clock::now()};
    time_t now_time { chrono::system_clock::to_time_t(now)};
    tm utc_tm { *gmtime(&now_time)};

    // print_match(kSample, re_common, "Common");
    // parse(kSample);

    return 0;
}
