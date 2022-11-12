/**
 * @file node.h
 * @author PANFACTORY (github.com/PANFACTORY)
 * @brief Node of AST
 * @version 0.1
 * @date 2022-09-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace JsonParser {
enum class ValueType {
    Default,
    String,
    Number,
    BoolNull,
    Object,
    Array,
};

/**
 * @brief   Node of AST
 *
 */
class Node {
   public:
    Node() = delete;
    /**
     * @brief       Construct a new Node object
     *
     * @param[in]   std::string _key    JSON key this node contains
     */
    Node(std::string _key) : object(0), array(0) {
        this->key = _key;
        this->value = "";
        this->valuetype = ValueType::Default;
    }
    Node(const Node& node) : object(0), array(0) {
        this->key = node.key;
        this->value = node.value;
        this->valuetype = node.valuetype;
        for (auto child : node.object) {
            this->object.push_back(new Node(*child));
        }
        for (auto child : node.array) {
            this->array.push_back(new Node(*child));
        }
    }
    ~Node() {
        for (auto child : this->object) {
            delete child;
        }
        for (auto child : this->array) {
            delete child;
        }
    }
    Node& operator=(const Node& node) {
        for (auto child : this->object) {
            delete child;
        }
        for (auto child : this->array) {
            delete child;
        }
        this->key = node.key;
        this->value = node.value;
        this->valuetype = node.valuetype;
        for (auto child : node.object) {
            this->object.push_back(new Node(*child));
        }
        for (auto child : node.array) {
            this->array.push_back(new Node(*child));
        }
        return *this;
    }

    /**
     * @brief       Set value to this node as String
     *
     * @param[in]   std::string _value  JSON value this node contains
     */
    void SetString(std::string _value) {
        this->value = _value;
        if (this->valuetype != ValueType::Default) {
            throw std::runtime_error(
                "At SetString() in Node class: Some value is already set.");
        }
        this->valuetype = ValueType::String;
    }

    /**
     * @brief       Set value to this node as Number
     *
     * @param[in]   std::string _value  JSON value this node contains
     */
    void SetNumber(std::string _value) {
        this->value = _value;
        if (this->valuetype != ValueType::Default) {
            throw std::runtime_error(
                "At SetNumber() in Node class: Some value is already set.");
        }
        this->valuetype = ValueType::Number;
    }

    /**
     * @brief       Set value to this node as Boolean or Null
     *
     * @param[in]   std::string _value  JSON value this node contains
     */
    void SetBoolNull(std::string _value) {
        this->value = _value;
        if (this->valuetype != ValueType::Default) {
            throw std::runtime_error(
                "At SetBoolNull() in Node class: Some value is already set.");
        }
        this->valuetype = ValueType::BoolNull;
    }

    /**
     * @brief       Append a child node as object
     *
     * @param[in]   JsonParser::Node* child Pointer indicating a child node
     * appended as object in this node
     */
    void AppendObject(Node* child = nullptr) {
        if (child != nullptr) {
            this->object.push_back(child);
        }
        if (this->valuetype != ValueType::Default &&
            this->valuetype != ValueType::Object) {
            throw std::runtime_error(
                "At AppendObject() in Node class: Some value not Object is "
                "alreadey set.");
        }
        this->valuetype = ValueType::Object;
    }

    /**
     * @brief       Append a child node as array
     *
     * @param[in]   JsonParser::Node* child Pointer indicating a child node
     * appended as array in this node
     */
    void AppendArray(Node* child = nullptr) {
        if (child != nullptr) {
            this->array.push_back(child);
        }
        if (this->valuetype != ValueType::Default &&
            this->valuetype != ValueType::Array) {
            throw std::runtime_error(
                "At AppendArray() in Node class: Some value not Array is "
                "alreadey set.");
        }
        this->valuetype = ValueType::Array;
    }

    /**
     * @brief       Return reference indicating a child node corresponding to
     * the key
     *
     * @param[in]   std::string _key    JSON key
     * @return      Json::Parser Node*  Reference indicating a child node
     * corresponding to the key
     */
    Node& operator[](std::string _key) {
        for (auto child : this->object) {
            if (child->key == _key) {
                return *child;
            }
        }
        throw std::runtime_error("Object containing this key doesn't exist.");
    }

    /**
     * @brief       Return reference indicating a node corresponding to the
     * index  of array
     *
     * @param[in]   unsigned integer _index index of array
     * @return      JsonParser::Node&       Reference indicating a node
     * corresponding to the index of array
     */
    Node& operator[](unsigned int _index) {
        if (_index < this->array.size()) {
            return *this->array[_index];
        }
        throw std::range_error("\"index\" is over length of Array.");
    }

    /**
     * @brief   Return reference indicating the value of node
     *
     * @return  std::string&    Reference indicating the value of node
     */
    std::string& Value() {
        if (this->valuetype == ValueType::String ||
            this->valuetype == ValueType::Number ||
            this->valuetype == ValueType::BoolNull) {
            return this->value;
        }
        throw std::runtime_error("Value doesn't exist.");
    }

    /**
     * @brief Return json data as std::string
     *
     * @return std::string json data which AST contains
     */
    std::string Str() {
        std::string str("");
        if (this->key != "") {
            str += "\"" + this->key + "\":";
        }
        switch (this->valuetype) {
            case ValueType::String:
                str += "\"" + this->value + "\"";
                break;
            case ValueType::Number:
            case ValueType::BoolNull:
                str += this->value;
                break;
            case ValueType::Object:
                str += "{";
                if (this->object.size() > 0) {
                    str += this->object[0]->Str();
                }
                for (int i = 1; i < this->object.size(); ++i) {
                    str += "," + this->object[i]->Str();
                }
                str += "}";
                break;
            case ValueType::Array:
                str += "[";
                if (this->array.size() > 0) {
                    str += this->array[0]->Str();
                }
                for (int i = 1; i < this->array.size(); ++i) {
                    str += "," + this->array[i]->Str();
                }
                str += "]";
                break;
            default:
                throw std::runtime_error(
                    "At Str() in Node class: This node has no content.");
        }
        return str;
    }

    /**
     * @brief Return size of array
     *
     * @return int size of array
     */
    unsigned int ArraySize() const { return this->array.size(); }

    /**
     * @brief Return list of object key
     *
     * @return std::vector<std::string> list of object key
     */
    std::vector<std::string> KeyList() const {
        std::vector<std::string> KeyList(0);
        for (const auto& node : this->object) {
            KeyList.push_back(node->key);
        }
        return KeyList;
    }

   private:
    std::string key, value;
    ValueType valuetype;
    std::vector<Node*> object, array;
};
}  // namespace JsonParser
