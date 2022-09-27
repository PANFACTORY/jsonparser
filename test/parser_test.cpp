#include <gtest/gtest.h>

#include "../src/parser.h"

TEST(JsonParserTest, ParserTest1) {
    std::vector<std::string> chs = {
        "{",
        "\"name\"",
        ":",
        "\"Tanaka\"",
        "}"
    };
    JsonParser::Node root("");
    ASSERT_EQ(JsonParser::Value(0, chs, &root), chs.size());
    std::cout << root << std::endl;
}

TEST(JsonParserTest, ParserTest2) {
    std::vector<std::string> chs = {
        "{",
        "\"name\"",
        ":",
        "\"Tanaka\"",
        ",",
        "\"age\"",
        ":",
        "26",
        "}"
    };
    JsonParser::Node root("");
    ASSERT_EQ(JsonParser::Value(0, chs, &root), chs.size());
    std::cout << root << std::endl;
}

TEST(JsonParserTest, ParserTest3) {
    std::vector<std::string> chs = {
        "[",
        "\"ABC\"",
        ",",
        "\"DEF\"",
        "]"
    };
    JsonParser::Node root("");
    ASSERT_EQ(JsonParser::Value(0, chs, &root), chs.size());
    std::cout << root << std::endl;
}

TEST(JsonParserTest, ParserTest4) {
    std::vector<std::string> chs = {
        "\"ABC\""
    };
    JsonParser::Node root("");
    ASSERT_EQ(JsonParser::Value(0, chs, &root), chs.size());
    std::cout << root << std::endl;
}

TEST(JsonParserTest, ParserTest5) {
    std::vector<std::string> chs = {
        "123"
    };
    JsonParser::Node root("");
    ASSERT_EQ(JsonParser::Value(0, chs, &root), chs.size());
    std::cout << root << std::endl;
}

TEST(JsonParserTest, ParserTest6) {
    std::vector<std::string> chs = {
        "{",
        "\"age\"",
        ":",
        "26",
        ",",
        "\"pi\"",
        ":",
        "3.14",
        ",",
        "\"planck_constant\"",
        ":",
        "6.62607e-34",
        ",",
        "\"negative_number\"",
        ":",
        "-123",
        "}"
    };
    JsonParser::Node root("");
    ASSERT_EQ(JsonParser::Value(0, chs, &root), chs.size());
    std::cout << root << std::endl;
}

TEST(JsonParserTest, ParserTest7) {
    std::vector<std::string> chs = {
        "{",
        "\"name\"",
        ":",
        "null",
        ",",
        "\"active_flag\"",
        ":",
        "true",
        ",",
        "\"delete_flag\"",
        ":",
        "false",
        "}"
    };
    JsonParser::Node root("");
    ASSERT_EQ(JsonParser::Value(0, chs, &root), chs.size());
    std::cout << root << std::endl;
}

TEST(JsonParserTest, ParserTest8) {
    std::vector<std::string> chs = {
        "{",
        "\"user_info\"",
        ":",
        "{",
        "\"user_id\"",
        ":",
        "\"A1234567\"",
        ",",
        "\"user_name\"",
        ":",
        "\"Yamada Taro\"",
        "}",
        "}"
    };
    JsonParser::Node root("");
    ASSERT_EQ(JsonParser::Value(0, chs, &root), chs.size());
    std::cout << root << std::endl;
}

TEST(JsonParserTest, ParserTest9) {
    std::vector<std::string> chs = {
        "{",
        "\"color_list\"",
        ":",
        "[",
        "\"red\"",
        ",",
        "\"green\"",
        ",",
        "\"blue\"",
        "]",
        ",",
        "\"num_list\"",
        ":",
        "[",
        "123",
        ",",
        "456",
        ",",
        "789",
        "]",
        ",",
        "\"mix_list\"",
        ":",
        "[",
        "\"red\"",
        ",",
        "456",
        ",",
        "null",
        ",",
        "true",
        "]",
        ",",
        "\"array_list\"",
        ":",
        "[",
        "[",
        "12",
        ",",
        "23",
        "]",
        ",",
        "[",
        "34",
        ",",
        "45",
        "]",
        ",",
        "[",
        "56",
        ",",
        "67",
        "]",
        "]",
        ",",
        "\"object_list\"",
        ":",
        "[",
        "{",
        "\"name\"",
        ":",
        "\"Tanaka\"",
        ",",
        "\"age\"",
        ":",
        "26",
        "}",
        ",",
        "{",
        "\"name\"",
        ":",
        "\"Suzuki\"",
        ",",
        "\"age\"",
        ":",
        "32",
        "}",
        "]",
        "}"
    };
    JsonParser::Node root("");
    ASSERT_EQ(JsonParser::Value(0, chs, &root), chs.size());
    std::cout << root << std::endl;
}
