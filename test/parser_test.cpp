#include <gtest/gtest.h>

#include "../src/parser.h"

TEST(JsonParserTest, ParserTest1) {
    std::vector<std::string> chs = {"\"ABC\""};
    JsonParser::Node* root = JsonParser::Parser(chs);
    std::cout << *root << std::endl;
    ASSERT_TRUE(true);
}

TEST(JsonParserTest, ParserTest2) {
    std::vector<std::string> chs = {"{", "}"};
    JsonParser::Node* root = JsonParser::Parser(chs);
    std::cout << *root << std::endl;
    ASSERT_TRUE(true);
}

TEST(JsonParserTest, ParserTest3) {
    std::vector<std::string> chs = {"{", "\"name\"", ":", "\"Tanaka\"", "}"};
    JsonParser::Node* root = JsonParser::Parser(chs);
    std::cout << *root << std::endl;
    ASSERT_TRUE(true);
}

TEST(JsonParserTest, LexicalTest4) {
    std::vector<std::string> chs = {"{", "\"name\"", ":", "\"Tanaka\"", ",", "\"age\"", ":", "\"26\"", "}"};
    JsonParser::Node* root = JsonParser::Parser(chs);
    std::cout << *root << std::endl;
    ASSERT_TRUE(true);
}

TEST(JsonParserTest, LexicalTest5) {
    std::vector<std::string> chs = {"{", "\"name\"", ":", "\"Tanaka\"", ",", "\"age\"", ":", "\"26\"", ",", "\"sex\"", ":", "\"male\"", "}"};
    JsonParser::Node* root = JsonParser::Parser(chs);
    std::cout << *root << std::endl;
    ASSERT_TRUE(true);
}

TEST(JsonParserTest, LexicalTest6) {
    std::vector<std::string> chs = {"{", "\"user_info\"", ":", "{", "\"user_id\"", ":", "\"A1234567\"", ",", "\"user_name\"", ":", "\"Yamada Taro\"", "}", "}"};
    JsonParser::Node* root = JsonParser::Parser(chs);
    std::cout << *root << std::endl;
    ASSERT_TRUE(true);
}
