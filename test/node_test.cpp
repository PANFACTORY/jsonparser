#include <gtest/gtest.h>

#include "../src/node.h"

TEST(JsonParserTest, NodeTest1) {
    JsonParser::Node root("");
    root.SetValue("\"ABC\"");
    std::cout << root << std::endl;
    ASSERT_TRUE(true);
}

TEST(JsonParserTest, NodeTest2) {
    JsonParser::Node root(""), *child = new JsonParser::Node("\"name\"");
    child->SetValue("\"Tanaka\"");
    root.SetChild(child);
    std::cout << root << std::endl;
    ASSERT_TRUE(true);
}

TEST(JsonParserTest, NodeTest3) {
    JsonParser::Node root("");
    JsonParser::Node *child1 = new JsonParser::Node("\"name\""), *child2 = new JsonParser::Node("\"age\"");
    child1->SetValue("\"Tanaka\"");
    root.SetChild(child1);
    child2->SetValue("26");
    root.SetChild(child2);
    std::cout << root << std::endl;
    ASSERT_TRUE(true);
}
