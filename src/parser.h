#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <cctype>

#include "node.h"

namespace JsonParser {
    int Value(int index, const std::vector<std::string> &chs, Node *node);

    int Object(int index, const std::vector<std::string> &chs, Node *parent) {
        std::cout << "Object is called " << index << std::endl;
        switch (chs[index][0]) {
        case '}':
            return index + 1;
        case '"':
            {
            Node* child = new Node(chs[index]);
            int index_current = Value(index + 2, chs, child);
            parent->SetChild(child);

            while (chs[index_current][0] == ',') {
                index_current += 1;
                child = new Node(chs[index_current]);
                index_current = Value(index_current + 2, chs, child);
                parent->SetChild(child);
            }

            return index_current + 1;
            }
        default:
            std::cout << "default at Object " << index << std::endl;
            return 0;
        }
    }

    int Value(int index, const std::vector<std::string> &chs, Node *node) {
        std::cout << "Value is called " << index << std::endl;
        switch (chs[index][0]) {
        case '"':
            node->SetValue(chs[index]);
            return index + 1;
        case '{':
            return Object(index + 1, chs, node);
        default:
            std::cout << "default at Value " << index << std::endl;
            return 0;
        }
    }

    // Parser
    Node* Parser(const std::vector<std::string> &chs) {
        Node* root = new Node("");
        std::cout << Value(0, chs, root) << std::endl;
        return root;
    }
}
