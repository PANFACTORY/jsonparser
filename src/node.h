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
        }
        Node(const Node&) = delete;
        ~Node() {
            for (auto child : this->children) {
                delete child;
            }
        }

        void SetValue(std::string _value) {
            this->value = _value;
            this->isvalueset = true;
        }

        void SetChild(Node* _node) {
            this->children.push_back(_node);
        }

        std::string key;
        std::string value;
        bool isvalueset;
        std::vector<Node*> children;
    };
}

std::ostream& operator<<(std::ostream& stream, const JsonParser::Node& node) {
    if (node.key != "") {
        stream << node.key << ":";
    }
    if (node.isvalueset) {
        stream << node.value;
    } else {
        stream << "{";
        if (node.children.size() > 0) {
            stream << *node.children[0];
        }
        for (int i = 1; i < node.children.size(); ++i) {
            stream << "," << *node.children[i];
        }
        stream << "}";
    }
    return stream;
}
