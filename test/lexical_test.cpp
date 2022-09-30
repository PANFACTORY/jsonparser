#include <gtest/gtest.h>

#include "../src/lexical.h"

// Happy path testing
TEST(JsonParserTest, LexicalHappyTest1) {
    std::stringstream ss;
    ss << R"({ "name": "Tanaka" })";
    std::vector<std::string> chs = JsonParser::LexicalAnalyzer(ss);
    ASSERT_EQ(chs.size(), 5);
}

TEST(JsonParserTest, LexicalHappyTest2) {
    std::stringstream ss;
    ss << R"({ "name": "Tanaka", "age": 26 })";
    std::vector<std::string> chs = JsonParser::LexicalAnalyzer(ss);
    ASSERT_EQ(chs.size(), 9);
}

TEST(JsonParserTest, LexicalHappyTest3) {
    std::stringstream ss;
    ss << R"(["ABC", "DEF"])";
    std::vector<std::string> chs = JsonParser::LexicalAnalyzer(ss);
    ASSERT_EQ(chs.size(), 5);
}

TEST(JsonParserTest, LexicalHappyTest4) {
    std::stringstream ss;
    ss << R"("ABC")";
    std::vector<std::string> chs = JsonParser::LexicalAnalyzer(ss);
    ASSERT_EQ(chs.size(), 1);
}

TEST(JsonParserTest, LexicalHappyTest5) {
    std::stringstream ss;
    ss << R"(123)";
    std::vector<std::string> chs = JsonParser::LexicalAnalyzer(ss);
    ASSERT_EQ(chs.size(), 1);
}

TEST(JsonParserTest, LexicalHappyTest6) {
    std::stringstream ss;
    ss << R"({ "age": 26, "pi": 3.14, "planck_constant": 6.62607e-34, "negative_number": -123 })";
    std::vector<std::string> chs = JsonParser::LexicalAnalyzer(ss);
    ASSERT_EQ(chs.size(), 17);
}

TEST(JsonParserTest, LexicalHappyTest7) {
    std::stringstream ss;
    ss << R"({ "name": null, "active_flag": true, "delete_flag": false })";
    std::vector<std::string> chs = JsonParser::LexicalAnalyzer(ss);
    ASSERT_EQ(chs.size(), 13);
}

TEST(JsonParserTest, LexicalHappyTest8) {
    std::stringstream ss;
    ss << R"({ "user_info": { "user_id": "A1234567", "user_name": "Yamada Taro" } })";
    std::vector<std::string> chs = JsonParser::LexicalAnalyzer(ss);
    ASSERT_EQ(chs.size(), 13);
}

TEST(JsonParserTest, LexicalHappyTest9) {
    std::stringstream ss;
    ss << R"({ "color_list": [ "red", "green", "blue" ], "num_list": [ 123, 456, 789 ], "mix_list": [ "red", 456, null, true ], "array_list": [ [ 12, 23 ], [ 34, 45 ], [ 56, 67 ] ], "object_list": [ { "name": "Tanaka", "age": 26 }, { "name": "Suzuki", "age": 32 } ] })";
    std::vector<std::string> chs = JsonParser::LexicalAnalyzer(ss);
    ASSERT_EQ(chs.size(), 79);
}

TEST(JsonParserTest, LexicalHappyTest10) {
    std::stringstream ss;
    ss << R"({ "key\"": "v]al:ue}" })";
    std::vector<std::string> chs = JsonParser::LexicalAnalyzer(ss);
    ASSERT_EQ(chs.size(), 5);
}

// Unhappy path testing
TEST(JsonParserTest, LexicalUnhappyTest1) {
    std::stringstream ss;
    ss << R"({ "active_flag" : trueth })";
    EXPECT_ANY_THROW(JsonParser::LexicalAnalyzer(ss));
}

TEST(JsonParserTest, LexicalUnhappyTest2) {
    std::stringstream ss;
    ss << R"({ "delete_flag" : failure })";
    EXPECT_ANY_THROW(JsonParser::LexicalAnalyzer(ss));
}

TEST(JsonParserTest, LexicalUnhappyTest3) {
    std::stringstream ss;
    ss << R"({ "name" : nullptr })";
    EXPECT_ANY_THROW(JsonParser::LexicalAnalyzer(ss));
}

TEST(JsonParserTest, LexicalUnhappyTest4) {
    std::stringstream ss;
    ss << R"({ "number" : 01 })";
    EXPECT_ANY_THROW(JsonParser::LexicalAnalyzer(ss));
}

TEST(JsonParserTest, LexicalUnhappyTest5) {
    std::stringstream ss;
    ss << R"({ "number" : -a })";
    EXPECT_ANY_THROW(JsonParser::LexicalAnalyzer(ss));
}

TEST(JsonParserTest, LexicalUnhappyTest6) {
    std::stringstream ss;
    ss << R"({ "number" : -- })";
    EXPECT_ANY_THROW(JsonParser::LexicalAnalyzer(ss));
}

TEST(JsonParserTest, LexicalUnhappyTest7) {
    std::stringstream ss;
    ss << R"({ "number" : 1.2.3 })";
    EXPECT_ANY_THROW(JsonParser::LexicalAnalyzer(ss));
}

TEST(JsonParserTest, LexicalUnhappyTest8) {
    std::stringstream ss;
    ss << R"({ "number" : 1a })";
    EXPECT_ANY_THROW(JsonParser::LexicalAnalyzer(ss));
}
