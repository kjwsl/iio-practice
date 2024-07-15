#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <regex>

using namespace std;

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

regex build_full_regex(const string& re) {
    static const string re_common_fron {R"(\$(GP|GB|GA|GL|GN|GI))"};
    static const string re_common_back {R"(\*([\dA-E]{2})\n)"};
    return regex(re_common_fron + re + re_common_back);
}


int main() {
    const string re_gsv {R"(GSV,(\d),(\d),(\d{2})((?:,\d{0,2}?,\d{0,2}?,\d{0,3}?,\d{0,2}?)*))"};
    const string re_gsa {R"(GSA,(\w),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*),(\d*)(?:,(\d+\.\d+)){3})"};
    const string re_rmc {R"(RMC,(\d{2})(\d{2})(\d{2}\.\d{3}),([AV]),(\d{2})(\d{2}\.\d{4}),([NS]),(\d{3})(\d{2}\.\d{4}),([EW]),(\d*\.\d*),(\d*\.\d*),(\d{2})(\d{2})(\d{2}),([EW]?),(E?),([ADE]))"};
    const string re_gll {R"(GLL,(\d{2})(\d{2}\.\d*),([NS]),(\d{3})(\d*\.\d*),([EW]),(\d{2})(\d{2})(\d*\.\d*),([AV]),([ADE]))"};
    const string re_vtg {R"(VTG,(\d*\.\d*)?,([TM]),(\d*\.\d*)?,([TM]),(\d*\.\d*),([NK]),(\d*\.\d*),([NK]),([ADE]))"};


    print_match(kSample, build_full_regex(re_gsv), "GSV");
    print_match(kSample, build_full_regex(re_gsa), "GSA");
    print_match(kSample, build_full_regex(re_rmc), "RMC");
    print_match(kSample, build_full_regex(re_gll), "GLL");
    print_match(kSample, build_full_regex(re_vtg), "VTG");
    


    return 0;
}
