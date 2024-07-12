#include <string_view>
#include <memory>
#include <gtest/gtest.h>
#include "../include/NmeaParser.h"
#include "../include/Tokenizer.h"

using namespace std;
using namespace gnss::impl;
using namespace ray::utils;


TEST(NmeaParserTestSuite, NmeaParserTestCode) {
    /*
       auto my_parser { NmeaParser()};
       const string_view nmea_sentence {"$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,,0000*5E"sv };

    auto nmea_data_ptr { my_parser.parse(nmea_sentence)};

    auto gga_data_ptr = unique_ptr<GgaData>(dynamic_cast<GgaData*>(nmea_data_ptr.release()));

    ASSERT_NE(gga_data_ptr, nullptr) << "Parsing returned nullptr";

    EXPECT_EQ(gga_data_ptr->talker_id,     TalkerId::GP);
    EXPECT_EQ(gga_data_ptr->message_type,  MessageType::GGA);
    EXPECT_EQ(gga_data_ptr->checksum,      0x5e);
    */
} 

class TokenizerTest : public testing::Test {
    protected:
        TokenizerTest() : tokenizer() {}
        void SetUp() override {
            tokenizer = Tokenizer{nmea_sentence, ","};
        }

        void TearDown() override {
        }

        static constexpr string_view nmea_sentence {"$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,,0000*5E"sv };
        Tokenizer tokenizer;

};


TEST_F(TokenizerTest, GetSeparatorTest) {
    EXPECT_EQ(tokenizer.get_separator(), ",");
}

TEST_F(TokenizerTest, GetSourceTest) {
    EXPECT_EQ(tokenizer.get_source(), nmea_sentence);
}

TEST_F(TokenizerTest, GetTokenSizeTest) {
    EXPECT_EQ(tokenizer.get_token_size(), 0);
}

TEST_F(TokenizerTest, HasMoreTokensTest) {
    EXPECT_EQ(tokenizer.has_more_tokens(), false);
}

TEST_F(TokenizerTest, GetNextTokenTest) {
    EXPECT_EQ(tokenizer.get_next_token(), nullopt);
}

TEST_F(TokenizerTest, TokenizedGetTokenSizeTest) {
    tokenizer.tokenize();
    EXPECT_EQ(tokenizer.get_token_size(), 15);
    tokenizer.get_next_token();
    EXPECT_EQ(tokenizer.get_token_size(), 14);
}


TEST_F(TokenizerTest, TokenizedHasMoreTokensTest) {
    tokenizer.tokenize();
    EXPECT_EQ(tokenizer.has_more_tokens(), true);
}

TEST_F(TokenizerTest, TokenizedGetNextTokenTest) {
    tokenizer.tokenize();
    EXPECT_EQ(tokenizer.get_next_token(), "$GPGGA");
}

TEST(TestTest, TestTestCode) {
    EXPECT_EQ(1, 1);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
