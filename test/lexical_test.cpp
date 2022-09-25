#include <gtest/gtest.h>

#include "../src/parser.h"

TEST(JsonParserTest, LexicalTest1) {
    std::stringstream ss;
    ss << "{ \"name\": \"Tanaka\" }";
    std::vector<std::string> chs = JsonParser::Parser(ss);
    ASSERT_EQ(chs.size(), 5);
}

TEST(JsonParserTest, LexicalTest2) {
    std::stringstream ss;
    ss << "{ \"name\": \"Tanaka\", \"age\": 26 }";
    std::vector<std::string> chs = JsonParser::Parser(ss);
    ASSERT_EQ(chs.size(), 9);
}

TEST(JsonParserTest, LexicalTest3) {
    std::stringstream ss;
    ss << "[\"ABC\", \"DEF\"]";
    std::vector<std::string> chs = JsonParser::Parser(ss);
    ASSERT_EQ(chs.size(), 5);
}

TEST(JsonParserTest, LexicalTest4) {
    std::stringstream ss;
    ss << "\"ABC\"";
    std::vector<std::string> chs = JsonParser::Parser(ss);
    ASSERT_EQ(chs.size(), 1);
}

TEST(JsonParserTest, LexicalTest5) {
    std::stringstream ss;
    ss << "123";
    std::vector<std::string> chs = JsonParser::Parser(ss);
    ASSERT_EQ(chs.size(), 1);
}

TEST(JsonParserTest, LexicalTest6) {
    std::stringstream ss;
    ss << "{ \"age\": 26, \"pi\": 3.14, \"planck_constant\": 6.62607e-34, \"negative_number\": -123 }";
    std::vector<std::string> chs = JsonParser::Parser(ss);
    ASSERT_EQ(chs.size(), 17);
}

TEST(JsonParserTest, LexicalTest7) {
    std::stringstream ss;
    ss << "{ \"name\": null, \"active_flag\": true, \"delete_flag\": false }";
    std::vector<std::string> chs = JsonParser::Parser(ss);
    ASSERT_EQ(chs.size(), 13);
}

TEST(JsonParserTest, LexicalTest8) {
    std::stringstream ss;
    ss << "{ \"user_info\": { \"user_id\": \"A1234567\", \"user_name\": \"Yamada Taro\" } }";
    std::vector<std::string> chs = JsonParser::Parser(ss);
    ASSERT_EQ(chs.size(), 13);
}

TEST(JsonParserTest, LexicalTest9) {
    std::stringstream ss;
    ss << "{ \"color_list\": [ \"red\", \"green\", \"blue\" ], \"num_list\": [ 123, 456, 789 ], \"mix_list\": [ \"red\", 456, null, true ], \"array_list\": [ [ 12, 23 ], [ 34, 45 ], [ 56, 67 ] ], \"object_list\": [ { \"name\": \"Tanaka\", \"age\": 26 }, { \"name\": \"Suzuki\", \"age\": 32 } ] }";
    std::vector<std::string> chs = JsonParser::Parser(ss);
    ASSERT_EQ(chs.size(), 79);
}
