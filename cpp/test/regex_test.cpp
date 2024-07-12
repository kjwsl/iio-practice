#include <algorithm>
#include <iostream>
#include <string>
#include <regex>

using namespace std;

const std::string& kSample{
    "$GPGGA,092750.000,5321.6802,N,00630.3372,W,1,8,1.03,61.7,M,55.2,M,,*76\n"
    "$GPGSA,A,3,10,07,05,02,29,04,08,13,,,,,1.72,1.03,1.38*0A\n"
    "$GPGSV,3,1,11,10,63,137,17,07,61,098,15,05,59,290,20,08,54,157,30*70\n"
    "$GPGSV,3,2,11,02,39,223,19,13,28,070,17,26,23,252,,04,14,186,14*79\n"
    "$GPGSV,3,3,11,29,09,301,24,16,09,020,,36,,,*76\n"
    "$GPRMC,092750.000,A,5321.6802,N,00630.3372,W,0.02,31.66,280511,,,A*43\n"
    "$GPGGA,092751.000,5321.6802,N,00630.3371,W,1,8,1.03,61.7,M,55.3,M,,*75\n"
    "$GPGSA,A,3,10,07,05,02,29,04,08,13,,,,,1.72,1.03,1.38*0A\n"
    "$GPGSV,3,1,11,10,63,137,17,07,61,098,15,05,59,290,20,08,54,157,30*70\n"
    "$GPGSV,3,2,11,02,39,223,16,13,28,070,17,26,23,252,,04,14,186,15*77\n"
    "$GPGSV,3,3,11,29,09,301,24,16,09,020,,36,,,*76\n"
    "$GPRMC,092751.000,A,5321.6802,N,00630.3371,W,0.06,31.66,280511,,,A*45\n"
    "$GBRMC,092751.000,A,5321.6802,N,00630.3371,W,0.06,31.66,280511,,,A*45\n"
};

struct NmeaData {
    vector<string> tokens;
    string msg;
    string talker_id;
    string msg_type;
    int checksum;
};

void print_match(const string& src, const regex& re, const string_view title = "") {
    if (!title.empty()) {
        cout << "*************************************" << endl;
        cout << title << endl;
        cout << "*************************************" << endl;
    }
    int i = 1;
    string text { src };
    smatch match{};

    while (regex_search(text, match, re)) {
        cout << i++ << ": " << "\n";
        cout << "\tMatch: " << match.str() << "\n";
        for (int j = 1; j < match.size(); j++) {
            cout << "\tCapture(" << j << "): " << match[j].str() << "\n";
        }
        text = match.suffix().str();
    } 

}


int main() {
    regex re_sentence {"\\$(GP|GB|GA|GL)(GSV|RMC|GGA|VTG),.*\\*([\\dA-F]{2})\\n"};
    regex re_gsv { "\\$(GP|GB|GA|GL)GSV,(\\d),(\\d),(\\d{2})(?:,(\\d{2}),(\\d{2}),(\\d{2}\\d),(\\d{2})?)*\\*([\\dA-F]{2})\\n"};
    regex re_gsa { "\\$(GP|GB|GA|GL)GSA,(\\w),(\\d*),(\\d*),(\\d*),(\\d*),(\\d*),(\\d*),(\\d*),(\\d*),(\\d*),(\\d*),(\\d*),(\\d*),(\\d*)(?:,(\\d+\\.\\d+)){3}\\*([\\dA-F]){2}"};

    print_match(kSample, re_gsv, "GSV");
    print_match(kSample, re_gsa, "GSA");
    return 0;
}
