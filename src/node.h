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

#include <string>
#include <vector>
#include <iostream>

namespace JsonParser {
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
        Node(std::string _key) : children(0), children_array(0) {
            this->key = _key;
            this->value = "";
            this->isvalueset = false;
            this->ischildrenset = false;
            this->isarrayset = false;
        }
        Node(const Node& node) : children(0), children_array(0) {
            this->key = node.key;
            this->value = node.value;
            this->isvalueset = node.isvalueset;
            this->ischildrenset = node.ischildrenset;
            this->isarrayset = node.isarrayset;
            for (auto node_child : node.children) {
                this->children.push_back(new Node(*node_child));
            }
            for (auto node_child : node.children_array) {
                this->children_array.push_back(new Node(*node_child));
            }
        }
        ~Node() {
            for (auto child : this->children) {
                delete child;
            }
            for (auto child : this->children_array) {
                delete child;
            }
        }
        Node& operator=(const Node& node) {
            for (auto child : this->children) {
                delete child;
            }
            for (auto child : this->children_array) {
                delete child;
            }
            this->key = node.key;
            this->value = node.value;
            this->isvalueset = node.isvalueset;
            this->ischildrenset = node.ischildrenset;
            this->isarrayset = node.isarrayset;
            for (auto node_child : node.children) {
                this->children.push_back(new Node(*node_child));
            }
            for (auto node_child : node.children_array) {
                this->children_array.push_back(new Node(*node_child));
            }
            return *this;
        }

        /**
         * @brief       Set value to this node
         *
         * @param[in]   std::string _value  JSON value this node contains
         */
        void SetValue(std::string _value) {
            this->value = _value;
            if (this->isvalueset) {
                throw std::runtime_error("At SetValue() in Node class: Value is set to node set value.");
            }
            this->isvalueset = true;
            if (this->ischildrenset) {
                throw std::runtime_error("At SetValue() in Node class: Value is set to node set object.");
            }
            if (this->isarrayset) {
                throw std::runtime_error("At SetValue() in Node class: Value is set to node set array.");
            }
        }

        /**
         * @brief       Append a child node
         *
         * @param[in]   JsonParser::Node* _node Pointer indicating a child node appended in this node
         */
        void AppendChild(Node* _node = nullptr) {
            if (_node != nullptr) {
                this->children.push_back(_node);
            }
            this->ischildrenset = true;
            if (this->isvalueset) {
                throw std::runtime_error("At AppendChild() in Node class: Object is set to node set value.");
            }
            if (this->isarrayset) {
                throw std::runtime_error("At AppendChild() in Node class: Object is set to node set array.");
            }
        }

        /**
         * @brief       Append a child node as array
         *
         * @param[in]   JsonParser::Node* _node Pointer indicating a child node appended as array in this node
         */
        void AppendArray(Node* _node = nullptr) {
            if (_node != nullptr) {
                this->children_array.push_back(_node);
            }
            this->isarrayset = true;
            if (this->isvalueset) {
                throw std::runtime_error("At AppendArray() in Node class: Array is set to node set value.");
            }
            if (this->ischildrenset) {
                throw std::runtime_error("At AppendArray() in Node class: Array is set to node set object.");
            }
        }

        /**
         * @brief       Return reference indicating a child node corresponding to the key
         *
         * @param[in]   std::string _key    JSON key
         * @return      Json::Parser Node*  Reference indicating a child node corresponding to the key
         */
        Node& operator[](std::string _key) {
            for (auto child : this->children) {
                if (child->key == _key) {
                    return *child;
                }
            }
            throw std::runtime_error("Object containing this key doesn't exist.");
        }

        /**
         * @brief       Return reference indicating a node corresponding to the index  of array
         *
         * @param[in]   unsigned integer _index index of array
         * @return      JsonParser::Node&       Reference indicating a node corresponding to the index of array
         */
        Node& operator[](unsigned int _index) {
            if (_index < this->children_array.size()) {
                return *this->children_array[_index];
            }
            throw std::range_error("\"index\" is over length of Array.");
        }

        /**
         * @brief   Return reference indicating the value of node
         *
         * @return  std::string&    Reference indicating the value of node
         */
        std::string& Value() {
            if (this-isvalueset) {
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
                str += this->key + ":";
            }
            if (this->isvalueset) {
                str += this->value;
            } else if (this->ischildrenset) {
                str += "{";
                if (this->children.size() > 0) {
                    str += this->children[0]->Str();
                }
                for (int i = 1; i < this->children.size(); ++i) {
                    str += "," + this->children[i]->Str();
                }
                str += "}";
            } else if (this->isarrayset) {
                str += "[";
                if (this->children_array.size() > 0) {
                    str += this->children_array[0]->Str();
                }
                for (int i = 1; i < this->children_array.size(); ++i) {
                    str += "," + this->children_array[i]->Str();
                }
                str += "]";
            } else {
                throw std::runtime_error("At operator<< of Node class: \"node\" is set neither value, object nor array.");
            }
            return str;
        }
private:
        std::string key, value;
        bool isvalueset, ischildrenset, isarrayset;
        std::vector<Node*> children, children_array;
    };
}
