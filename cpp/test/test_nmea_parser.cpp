#include <string_view>
#include <memory>
#include <gtest/gtest.h>
#include "../src/include/NmeaParser.h"

using namespace std;
using namespace gnss::impl;


TEST(NmeaParserTestSuite, NmeaParserTestCode) {
    auto my_parser { NmeaParser()};
    const string_view nmea_sentence {"$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,,0000*5E"sv };

    auto nmea_data_ptr { my_parser.parse(nmea_sentence)};

    auto gga_data_ptr = unique_ptr<GgaData>(dynamic_cast<GgaData*>(nmea_data_ptr.release()));

    ASSERT_NE(gga_data_ptr, nullptr) << "Parsing returned nullptr";

    EXPECT_EQ(gga_data_ptr->talker_id,     TalkerId::GP);
    EXPECT_EQ(gga_data_ptr->message_type,  MessageType::GGA);
    EXPECT_EQ(gga_data_ptr->checksum,      0x5e);
} 

TEST(TestTest, TestTestCode) {
    EXPECT_EQ(1, 1);

}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
