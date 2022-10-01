#include <gtest/gtest.h>

#include "../src/node.h"

// Happy path testing
TEST(JsonParserTest, NodeHappyTest1) {
    JsonParser::Node root(""), *child = new JsonParser::Node("name");
    child->SetString("Tanaka");
    root.AppendObject(child);
    ASSERT_EQ(root.Str(), R"({"name":"Tanaka"})");
}

TEST(JsonParserTest, NodeHappyTest2) {
    JsonParser::Node root("");
    JsonParser::Node *child1 = new JsonParser::Node("name"), *child2 = new JsonParser::Node("age");
    child1->SetString("Tanaka");
    root.AppendObject(child1);
    child2->SetNumber("26");
    root.AppendObject(child2);
    ASSERT_EQ(root.Str(), R"({"name":"Tanaka","age":26})");
}

TEST(JsonParserTest, NodeHappyTest3) {
    JsonParser::Node root("");
    JsonParser::Node *child1 = new JsonParser::Node(""), *child2 = new JsonParser::Node("");
    child1->SetString("ABC");
    root.AppendArray(child1);
    child2->SetString("DEF");
    root.AppendArray(child2);
    ASSERT_EQ(root.Str(), R"(["ABC","DEF"])");
}

TEST(JsonParserTest, NodeHappyTest4) {
    JsonParser::Node root("");
    root.SetString("ABC");
    ASSERT_EQ(root.Str(), R"("ABC")");
}

TEST(JsonParserTest, NodeHappyTest8) {
    JsonParser::Node root("");
    JsonParser::Node *child1 = new JsonParser::Node("user_info");
    JsonParser::Node *child11 = new JsonParser::Node("user_id"), *child12 = new JsonParser::Node("user_name");
    child11->SetString("A1234567");
    child1->AppendObject(child11);
    child12->SetString("Yamada Taro");
    child1->AppendObject(child12);
    root.AppendObject(child1);
    ASSERT_EQ(root.Str(), R"({"user_info":{"user_id":"A1234567","user_name":"Yamada Taro"}})");
}

TEST(JsonParserTest, NodeHappyTest9) {
    JsonParser::Node root("");
    JsonParser::Node *child1 = new JsonParser::Node("color_list");
    JsonParser::Node *child11 = new JsonParser::Node(""), *child12 = new JsonParser::Node(""), *child13 = new JsonParser::Node("");
    child11->SetString("red");
    child1->AppendArray(child11);
    child12->SetString("green");
    child1->AppendArray(child12);
    child13->SetString("blue");
    child1->AppendArray(child13);
    root.AppendObject(child1);
    JsonParser::Node *child2 = new JsonParser::Node("num_list");
    JsonParser::Node *child21 = new JsonParser::Node(""), *child22 = new JsonParser::Node(""), *child23 = new JsonParser::Node("");
    child21->SetNumber("123");
    child2->AppendArray(child21);
    child22->SetNumber("456");
    child2->AppendArray(child22);
    child23->SetNumber("789");
    child2->AppendArray(child23);
    root.AppendObject(child2);
    JsonParser::Node *child3 = new JsonParser::Node("mix_list");
    JsonParser::Node *child31 = new JsonParser::Node(""), *child32 = new JsonParser::Node(""), *child33 = new JsonParser::Node(""), *child34 = new JsonParser::Node("");
    child31->SetString("red");
    child3->AppendArray(child31);
    child32->SetNumber("456");
    child3->AppendArray(child32);
    child33->SetBoolNull("null");
    child3->AppendArray(child33);
    child34->SetBoolNull("true");
    child3->AppendArray(child34);
    root.AppendObject(child3);
    JsonParser::Node *child4 = new JsonParser::Node("array_list");
    JsonParser::Node *child41 = new JsonParser::Node(""), *child42 = new JsonParser::Node(""), *child43 = new JsonParser::Node("");
    JsonParser::Node *child411 = new JsonParser::Node(""), *child412 = new JsonParser::Node("");
    child411->SetNumber("12");
    child41->AppendArray(child411);
    child412->SetNumber("23");
    child41->AppendArray(child412);
    child4->AppendArray(child41);
    JsonParser::Node *child421 = new JsonParser::Node(""), *child422 = new JsonParser::Node("");
    child421->SetNumber("34");
    child42->AppendArray(child421);
    child422->SetNumber("45");
    child42->AppendArray(child422);
    child4->AppendArray(child42);
    JsonParser::Node *child431 = new JsonParser::Node(""), *child432 = new JsonParser::Node("");
    child431->SetNumber("56");
    child43->AppendArray(child431);
    child432->SetNumber("67");
    child43->AppendArray(child432);
    child4->AppendArray(child43);
    root.AppendObject(child4);
    JsonParser::Node *child5 = new JsonParser::Node("object_list");
    JsonParser::Node *child51 = new JsonParser::Node(""), *child52 = new JsonParser::Node("");
    JsonParser::Node *child511 = new JsonParser::Node("name"), *child512 = new JsonParser::Node("age");
    child511->SetString("Tanaka");
    child51->AppendObject(child511);
    child512->SetNumber("26");
    child51->AppendObject(child512);
    child5->AppendArray(child51);
    JsonParser::Node *child521 = new JsonParser::Node("name"), *child522 = new JsonParser::Node("age");
    child521->SetString("Suzuki");
    child52->AppendObject(child521);
    child522->SetNumber("32");
    child52->AppendObject(child522);
    child5->AppendArray(child52);
    root.AppendObject(child5);
    ASSERT_EQ(root.Str(), R"({"color_list":["red","green","blue"],"num_list":[123,456,789],"mix_list":["red",456,null,true],"array_list":[[12,23],[34,45],[56,67]],"object_list":[{"name":"Tanaka","age":26},{"name":"Suzuki","age":32}]})");
}

TEST(JsonParserTest, NodeHappyTest10) {
    JsonParser::Node root(""), *child = new JsonParser::Node("name");
    child->SetString("Tanaka");
    root.AppendObject(child);
    ASSERT_EQ(root["name"].Value(), "Tanaka");
}

TEST(JsonParserTest, NodeHappyTest12) {
    JsonParser::Node root("");
    JsonParser::Node *child1 = new JsonParser::Node(""), *child2 = new JsonParser::Node("");
    child1->SetString("ABC");
    root.AppendArray(child1);
    child2->SetString("DEF");
    root.AppendArray(child2);
    ASSERT_EQ(root[0].Value(), "ABC");
    ASSERT_EQ(root[1].Value(), "DEF");
}

TEST(JsonParserTest, NodeHappyTest14) {
    JsonParser::Node root("");
    JsonParser::Node *child1 = new JsonParser::Node("user_info");
    JsonParser::Node *child11 = new JsonParser::Node("user_id"), *child12 = new JsonParser::Node("user_name");
    child11->SetString("A1234567");
    child1->AppendObject(child11);
    child12->SetString("Yamada Taro");
    child1->AppendObject(child12);
    root.AppendObject(child1);
    ASSERT_EQ(root["user_info"]["user_id"].Value(), "A1234567");
    ASSERT_EQ(root["user_info"]["user_name"].Value(), "Yamada Taro");
}

TEST(JsonParserTest, NodeHappyTest15) {
    JsonParser::Node root(""), *child = new JsonParser::Node("name");
    child->SetString("Tanaka");
    root.AppendObject(child);
    JsonParser::Node root2 = root;
    ASSERT_EQ(root["name"].Value(), root2["name"].Value());
    ASSERT_NE(&root["name"], &root2["name"]);
}

// Unhappy path testing
TEST(JsonParserTest, NodeUnhappyTest1) {
    JsonParser::Node root("name");
    EXPECT_ANY_THROW(root.Str());
}

TEST(JsonParserTest, NodeUnhappyTest2) {
    JsonParser::Node root("name");
    root.SetString("Tanaka");
    EXPECT_ANY_THROW(root.SetString("Tanaka"));
}

TEST(JsonParserTest, NodeUnhappyTest3) {
    JsonParser::Node root("name");
    JsonParser::Node *child = new JsonParser::Node("name");
    root.AppendObject(child);
    EXPECT_ANY_THROW(root.SetString("Tanaka"));
}

TEST(JsonParserTest, NodeUnhappyTest4) {
    JsonParser::Node root("name");
    JsonParser::Node *child = new JsonParser::Node("name");
    root.AppendArray(child);
    EXPECT_ANY_THROW(root.SetString("Tanaka"));
}

TEST(JsonParserTest, NodeUnhappyTest5) {
    JsonParser::Node root("name");
    root.SetString("Tanaka");
    EXPECT_ANY_THROW(root.AppendObject());
}

TEST(JsonParserTest, NodeUnhappyTest6) {
    JsonParser::Node root("name");
    JsonParser::Node *child1 = new JsonParser::Node("name");
    root.AppendArray(child1);
    EXPECT_ANY_THROW(root.AppendObject());
}

TEST(JsonParserTest, NodeUnhappyTest7) {
    JsonParser::Node root("name");
    root.SetString("Tanaka");
    JsonParser::Node *child = new JsonParser::Node("name");
    EXPECT_ANY_THROW(root.AppendObject(child));
}

TEST(JsonParserTest, NodeUnhappyTest8) {
    JsonParser::Node root("name");
    JsonParser::Node *child1 = new JsonParser::Node("name"), *child2 = new JsonParser::Node("name");
    root.AppendArray(child1);
    EXPECT_ANY_THROW(root.AppendObject(child2));
}

TEST(JsonParserTest, NodeUnhappyTest9) {
    JsonParser::Node root("name");
    root.SetString("Tanaka");
    EXPECT_ANY_THROW(root.AppendArray());
}

TEST(JsonParserTest, NodeUnhappyTest10) {
    JsonParser::Node root("name");
    JsonParser::Node *child1 = new JsonParser::Node("name");
    root.AppendObject(child1);
    EXPECT_ANY_THROW(root.AppendArray());
}

TEST(JsonParserTest, NodeUnhappyTest11) {
    JsonParser::Node root("name");
    root.SetString("Tanaka");
    JsonParser::Node *child = new JsonParser::Node("name");
    EXPECT_ANY_THROW(root.AppendArray(child));
}

TEST(JsonParserTest, NodeUnhappyTest12) {
    JsonParser::Node root("name");
    JsonParser::Node *child1 = new JsonParser::Node("name"), *child2 = new JsonParser::Node("name");
    root.AppendObject(child1);
    EXPECT_ANY_THROW(root.AppendArray(child2));
}
