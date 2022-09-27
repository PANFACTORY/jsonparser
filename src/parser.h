#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <cctype>

#include "node.h"

namespace JsonParser {
    int Value(int index, const std::vector<std::string> &chs, Node *node);

    int Array(int index, const std::vector<std::string> &chs, Node *parent) {
        std::cout << "Array() is called and index is " << index << std::endl;
        // TODO: indexがchs.sizeを越えていないかチェック
        switch (chs[index][0]) {
        case ']':
            // TODO: 空の配列なのか空のオブジェクトなのかを区別する
            return index + 1;
        case '"':
        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case 'n':
        case 't':
        case 'f':
        case '{':
        case '[':
            {
            Node* child = new Node("");
            int index_current = Value(index, chs, child);
            parent->SetArray(child);

            while (chs[index_current][0] == ',') {
                index_current += 1;
                // TODO: chs[index_current][0]のチェック
                child = new Node("");
                index_current = Value(index_current, chs, child);
                parent->SetArray(child);
            }

            return index_current + 1;
            }
        default:
            std::cout << "default at Array() and index is " << index << std::endl;
            return 0;
        }
        return 0;
    }

    int Object(int index, const std::vector<std::string> &chs, Node *parent) {
        // TODO: indexがchs.sizeを越えていないかチェック
        std::cout << "Object() is called and index is " << index << std::endl;
        switch (chs[index][0]) {
        case '}':
            // TODO: 空の配列なのか空のオブジェクトなのかを区別する
            return index + 1;
        case '"':
            {
            Node* child = new Node(chs[index]);
            int index_current = Value(index + 2, chs, child);
            parent->SetChild(child);

            while (chs[index_current][0] == ',') {
                index_current += 1;
                // TODO: chs[index_current][0]のチェック
                child = new Node(chs[index_current]);
                index_current = Value(index_current + 2, chs, child);
                parent->SetChild(child);
            }

            return index_current + 1;
            }
        default:
            std::cout << "default at Object() and index is " << index << std::endl;
            return 0;
        }
    }

    int Value(int index, const std::vector<std::string> &chs, Node *node) {
        // TODO: indexがchs.sizeを越えていないかチェック
        std::cout << "Value() is called and index is " << index << std::endl;
        switch (chs[index][0]) {
        case '"':
        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case 'n':
        case 't':
        case 'f':
            node->SetValue(chs[index]);
            return index + 1;
        case '{':
            return Object(index + 1, chs, node);
        case '[':
            return Array(index + 1, chs, node);
        default:
            std::cout << "default at Value() and index is " << index << std::endl;
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
