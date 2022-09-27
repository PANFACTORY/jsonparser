#pragma once

#include <string>
#include <vector>
#include <iostream>

namespace JsonParser {
    // Node
    class Node {
public:
        Node() = delete;
        Node(std::string _key) {
            this->key = _key;
            this->isvalueset = false;
            this->ischildrenset = false;
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
        }

        void SetChild(Node* _node) {
            this->children.push_back(_node);
            this->ischildrenset = true;
        }

        void SetArray(Node* _node) {
            this->children_array.push_back(_node);
        }

        std::string key, value;
        bool isvalueset, ischildrenset;
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
    } else {
        stream << "[";
        if (node.children_array.size() > 0) {
            stream << *node.children_array[0];
        }
        for (int i = 1; i < node.children_array.size(); ++i) {
            stream << "," << *node.children_array[i];
        }
        stream << "]";
    }
    return stream;
}
