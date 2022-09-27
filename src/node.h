#pragma once

#include <string>
#include <vector>
#include <iostream>

namespace JsonParser {
    class Node;
}

std::ostream& operator<<(std::ostream& stream, const JsonParser::Node& node);

namespace JsonParser {
    // Node
    class Node {
        friend std::ostream& ::operator<<(std::ostream& stream, const JsonParser::Node& node);
public:
        Node() = delete;
        Node(std::string _key) {
            this->key = _key;
            this->isvalueset = false;
            this->ischildrenset = false;
            this->isarrayset = false;
        }
        Node(const Node&) = delete;
        ~Node() {
            for (auto child : this->children) {
                delete child;
            }
            for (auto child : this->children_array) {
                delete child;
            }
        }

        void SetValue(std::string _value) {
            this->value = _value;
            this->isvalueset = true;
            // TODO: 既にオブジェクトや配列がセットされている場合にはエラーを出す。
        }

        void SetChild() {
            this->ischildrenset = true;
            // TODO: 既に値や配列がセットされている場合にはエラーを出す。
        }

        void SetChild(Node* _node) {
            this->children.push_back(_node);
            this->ischildrenset = true;
            // TODO: 既に値や配列がセットされている場合にはエラーを出す。
        }

        void SetArray() {
            this->isarrayset = true;
            // TODO: 既に値やオブジェクトがセットされている場合にはエラーを出す。
        }

        void SetArray(Node* _node) {
            this->children_array.push_back(_node);
            this->isarrayset = true;
            // TODO: 既に値やオブジェクトがセットされている場合にはエラーを出す。
        }

private:
        std::string key, value;
        bool isvalueset, ischildrenset, isarrayset;
        std::vector<Node*> children, children_array;
    };
}

std::ostream& operator<<(std::ostream& stream, const JsonParser::Node& node) {
    if (node.key != "") {
        stream << node.key << ":";
    }
    if (node.isvalueset) {
        stream << node.value;
    } else if (node.ischildrenset) {
        stream << "{";
        if (node.children.size() > 0) {
            stream << *node.children[0];
        }
        for (int i = 1; i < node.children.size(); ++i) {
            stream << "," << *node.children[i];
        }
        stream << "}";
    } else if (node.isarrayset) {
        stream << "[";
        if (node.children_array.size() > 0) {
            stream << *node.children_array[0];
        }
        for (int i = 1; i < node.children_array.size(); ++i) {
            stream << "," << *node.children_array[i];
        }
        stream << "]";
    } else {
        // TODO: ここでエラーを出す。
    }
    return stream;
}
