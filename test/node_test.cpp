#include <gtest/gtest.h>

#include "../src/node.h"

// Happy path testing
TEST(JsonParserTest, NodeHappyTest1) {
    JsonParser::Node root(""), *child = new JsonParser::Node("\"name\"");
    child->SetValue("\"Tanaka\"");
    root.SetChild(child);
    std::stringstream ss;
    ss << root;
    ASSERT_EQ(ss.str(), "{\"name\":\"Tanaka\"}");
}

TEST(JsonParserTest, NodeHappyTest2) {
    JsonParser::Node root("");
    JsonParser::Node *child1 = new JsonParser::Node("\"name\""), *child2 = new JsonParser::Node("\"age\"");
    child1->SetValue("\"Tanaka\"");
    root.SetChild(child1);
    child2->SetValue("26");
    root.SetChild(child2);
    std::stringstream ss;
    ss << root;
    ASSERT_EQ(ss.str(), "{\"name\":\"Tanaka\",\"age\":26}");
}

TEST(JsonParserTest, NodeHappyTest3) {
    JsonParser::Node root("");
    JsonParser::Node *child1 = new JsonParser::Node(""), *child2 = new JsonParser::Node("");
    child1->SetValue("\"ABC\"");
    root.SetArray(child1);
    child2->SetValue("\"DEF\"");
    root.SetArray(child2);
    std::stringstream ss;
    ss << root;
    ASSERT_EQ(ss.str(), "[\"ABC\",\"DEF\"]");
}

TEST(JsonParserTest, NodeHappyTest4) {
    JsonParser::Node root("");
    root.SetValue("\"ABC\"");
    std::stringstream ss;
    ss << root;
    ASSERT_EQ(ss.str(), "\"ABC\"");
}

TEST(JsonParserTest, NodeHappyTest8) {
    JsonParser::Node root("");
    JsonParser::Node *child1 = new JsonParser::Node("\"user_info\"");
    JsonParser::Node *child11 = new JsonParser::Node("\"user_id\""), *child12 = new JsonParser::Node("\"user_name\"");
    child11->SetValue("\"A1234567\"");
    child1->SetChild(child11);
    child12->SetValue("\"Yamada Taro\"");
    child1->SetChild(child12);
    root.SetChild(child1);
    std::stringstream ss;
    ss << root;
    ASSERT_EQ(ss.str(), "{\"user_info\":{\"user_id\":\"A1234567\",\"user_name\":\"Yamada Taro\"}}");
}

TEST(JsonParserTest, NodeHappyTest9) {
    JsonParser::Node root("");
    JsonParser::Node *child1 = new JsonParser::Node("\"color_list\"");
    JsonParser::Node *child11 = new JsonParser::Node(""), *child12 = new JsonParser::Node(""), *child13 = new JsonParser::Node("");
    child11->SetValue("\"red\"");
    child1->SetArray(child11);
    child12->SetValue("\"green\"");
    child1->SetArray(child12);
    child13->SetValue("\"blue\"");
    child1->SetArray(child13);
    root.SetChild(child1);
    JsonParser::Node *child2 = new JsonParser::Node("\"num_list\"");
    JsonParser::Node *child21 = new JsonParser::Node(""), *child22 = new JsonParser::Node(""), *child23 = new JsonParser::Node("");
    child21->SetValue("123");
    child2->SetArray(child21);
    child22->SetValue("456");
    child2->SetArray(child22);
    child23->SetValue("789");
    child2->SetArray(child23);
    root.SetChild(child2);
    JsonParser::Node *child3 = new JsonParser::Node("\"mix_list\"");
    JsonParser::Node *child31 = new JsonParser::Node(""), *child32 = new JsonParser::Node(""), *child33 = new JsonParser::Node(""), *child34 = new JsonParser::Node("");
    child31->SetValue("\"red\"");
    child3->SetArray(child31);
    child32->SetValue("456");
    child3->SetArray(child32);
    child33->SetValue("null");
    child3->SetArray(child33);
    child34->SetValue("true");
    child3->SetArray(child34);
    root.SetChild(child3);
    JsonParser::Node *child4 = new JsonParser::Node("\"array_list\"");
    JsonParser::Node *child41 = new JsonParser::Node(""), *child42 = new JsonParser::Node(""), *child43 = new JsonParser::Node("");
    JsonParser::Node *child411 = new JsonParser::Node(""), *child412 = new JsonParser::Node("");
    child411->SetValue("12");
    child41->SetArray(child411);
    child412->SetValue("23");
    child41->SetArray(child412);
    child4->SetArray(child41);
    JsonParser::Node *child421 = new JsonParser::Node(""), *child422 = new JsonParser::Node("");
    child421->SetValue("34");
    child42->SetArray(child421);
    child422->SetValue("45");
    child42->SetArray(child422);
    child4->SetArray(child42);
    JsonParser::Node *child431 = new JsonParser::Node(""), *child432 = new JsonParser::Node("");
    child431->SetValue("56");
    child43->SetArray(child431);
    child432->SetValue("67");
    child43->SetArray(child432);
    child4->SetArray(child43);
    root.SetChild(child4);
    JsonParser::Node *child5 = new JsonParser::Node("\"object_list\"");
    JsonParser::Node *child51 = new JsonParser::Node(""), *child52 = new JsonParser::Node("");
    JsonParser::Node *child511 = new JsonParser::Node("\"name\""), *child512 = new JsonParser::Node("\"age\"");
    child511->SetValue("\"Tanaka\"");
    child51->SetChild(child511);
    child512->SetValue("26");
    child51->SetChild(child512);
    child5->SetArray(child51);
    JsonParser::Node *child521 = new JsonParser::Node("\"name\""), *child522 = new JsonParser::Node("\"age\"");
    child521->SetValue("\"Suzuki\"");
    child52->SetChild(child521);
    child522->SetValue("32");
    child52->SetChild(child522);
    child5->SetArray(child52);
    root.SetChild(child5);
    std::stringstream ss;
    ss << root;
    ASSERT_EQ(ss.str(), "{\"color_list\":[\"red\",\"green\",\"blue\"],\"num_list\":[123,456,789],\"mix_list\":[\"red\",456,null,true],\"array_list\":[[12,23],[34,45],[56,67]],\"object_list\":[{\"name\":\"Tanaka\",\"age\":26},{\"name\":\"Suzuki\",\"age\":32}]}");
}

// Unhappy path testing
TEST(JsonParserTest, NodeUnhappyTest1) {
    JsonParser::Node root("\"name\"");
    std::stringstream ss;
    EXPECT_ANY_THROW(ss << root);
}

TEST(JsonParserTest, NodeUnhappyTest2) {
    JsonParser::Node root("\"name\"");
    root.SetValue("\"Tanaka\"");
    EXPECT_ANY_THROW(root.SetValue("\"Tanaka\""));
}

TEST(JsonParserTest, NodeUnhappyTest3) {
    JsonParser::Node root("\"name\"");
    JsonParser::Node *child = new JsonParser::Node("\"name\"");
    root.SetChild(child);
    EXPECT_ANY_THROW(root.SetValue("\"Tanaka\""));
}

TEST(JsonParserTest, NodeUnhappyTest4) {
    JsonParser::Node root("\"name\"");
    JsonParser::Node *child = new JsonParser::Node("\"name\"");
    root.SetArray(child);
    EXPECT_ANY_THROW(root.SetValue("\"Tanaka\""));
}

TEST(JsonParserTest, NodeUnhappyTest5) {
    JsonParser::Node root("\"name\"");
    root.SetValue("\"Tanaka\"");
    EXPECT_ANY_THROW(root.SetChild());
}

TEST(JsonParserTest, NodeUnhappyTest6) {
    JsonParser::Node root("\"name\"");
    JsonParser::Node *child1 = new JsonParser::Node("\"name\"");
    root.SetArray(child1);
    EXPECT_ANY_THROW(root.SetChild());
}

TEST(JsonParserTest, NodeUnhappyTest7) {
    JsonParser::Node root("\"name\"");
    root.SetValue("\"Tanaka\"");
    JsonParser::Node *child = new JsonParser::Node("\"name\"");
    EXPECT_ANY_THROW(root.SetChild(child));
}

TEST(JsonParserTest, NodeUnhappyTest8) {
    JsonParser::Node root("\"name\"");
    JsonParser::Node *child1 = new JsonParser::Node("\"name\""), *child2 = new JsonParser::Node("\"name\"");
    root.SetArray(child1);
    EXPECT_ANY_THROW(root.SetChild(child2));
}

TEST(JsonParserTest, NodeUnhappyTest9) {
    JsonParser::Node root("\"name\"");
    root.SetValue("\"Tanaka\"");
    EXPECT_ANY_THROW(root.SetArray());
}

TEST(JsonParserTest, NodeUnhappyTest10) {
    JsonParser::Node root("\"name\"");
    JsonParser::Node *child1 = new JsonParser::Node("\"name\"");
    root.SetChild(child1);
    EXPECT_ANY_THROW(root.SetArray());
}

TEST(JsonParserTest, NodeUnhappyTest11) {
    JsonParser::Node root("\"name\"");
    root.SetValue("\"Tanaka\"");
    JsonParser::Node *child = new JsonParser::Node("\"name\"");
    EXPECT_ANY_THROW(root.SetArray(child));
}

TEST(JsonParserTest, NodeUnhappyTest12) {
    JsonParser::Node root("\"name\"");
    JsonParser::Node *child1 = new JsonParser::Node("\"name\""), *child2 = new JsonParser::Node("\"name\"");
    root.SetChild(child1);
    EXPECT_ANY_THROW(root.SetArray(child2));
}
