/**
 * @file parser.h
 * @author PANFACTORY (github.com/PANFACTORY)
 * @brief Parser of JSON
 * @version 0.1
 * @date 2022-09-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <cctype>

#include "node.h"

namespace JsonParser {
    int Value(int index, const std::vector<std::string> &chs, Node *node);

    /**
     * @brief       Process <Array> in recursive descent parser.
     *
     * @param[in]   int index                           Current position in token array
     * @param[in]   const std::vector<std::string> &chs Token array from lexical analyzer
     * @param[in]   JsonParser::Node *parent            Pointer indicating the current AST node
     * @return      int                                 Updated position in token array
     */
    int Array(int index, const std::vector<std::string> &chs, Node *parent) {
        if (index >= chs.size()) {
            throw std::range_error("At Array(): \"index\" is over length of \"chs\".");
        }
        // std::cout << "Array() is called and index is " << index << std::endl;
        switch (chs[index][0]) {
        case ']':
            parent->SetArray();
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

            while (index_current < chs.size() && chs[index_current][0] == ',') {
                child = new Node("");
                index_current = Value(index_current + 1, chs, child);
                parent->SetArray(child);
            }

            return index_current + 1;
            }
        default:
            throw std::range_error("At Array(): Unexpected error occurs.");
            return 0;
        }
    }

    /**
     * @brief       Process <Object> in recursive descent parser.
     *
     * @param[in]   int index                           Current position in token array
     * @param[in]   const std::vector<std::string> &chs Token array from lexical analyzer
     * @param[in]   JsonParser::Node *parent            Pointer indicating the current AST node
     * @return      int                                 Updated position in token array
     */
    int Object(int index, const std::vector<std::string> &chs, Node *parent) {
        if (index >= chs.size()) {
            throw std::range_error("At Object(): \"index\" is over length of \"chs\".");
        }
        // std::cout << "Object() is called and index is " << index << std::endl;
        switch (chs[index][0]) {
        case '}':
            parent->SetChild();
            return index + 1;
        case '"':
            {
            Node* child = new Node(chs[index]);
            int index_current = Value(index + 2, chs, child);
            parent->SetChild(child);

            while (index_current < chs.size() && chs[index_current][0] == ',') {
                // Check exists "key" of next object.
                if (index_current + 1 >= chs.size()) {
                    throw std::range_error("At Object(): \"index\" is over length of \"chs\".");
                }
                if (chs[index_current + 1][0] != '"') {
                    throw std::runtime_error("At Object(): '\"' is expected, however other character is set.");
                }
                child = new Node(chs[index_current + 1]);

                // Check exists ":" between "key" and Value.
                if (index_current + 2 >= chs.size()) {
                    throw std::range_error("At Object(): \"index\" is over length of \"chs\".");
                }
                if (chs[index_current + 2][0] != ':') {
                    throw std::runtime_error("At Object(): \":\" is expected, however other character is set.");
                }

                index_current = Value(index_current + 3, chs, child);
                parent->SetChild(child);
            }

            return index_current + 1;
            }
        default:
            throw std::range_error("At Object(): Unexpected error occurs.");
            return 0;
        }
    }

    /**
     * @brief       Process <Value> in recursive descent parser.
     *
     * @param[in]   int index                           Current position in token array
     * @param[in]   const std::vector<std::string> &chs Token array from lexical analyzer
     * @param[in]   JsonParser::Node *node              Pointer indicating the current AST node
     * @return      int                                 Updated position in token array
     */
    int Value(int index, const std::vector<std::string> &chs, Node *node) {
        if (index >= chs.size()) {
            throw std::range_error("At Value(): \"index\" is over length of \"chs\".");
        }
        // std::cout << "Value() is called and index is " << index << std::endl;
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
            throw std::range_error("At Value(): Unexpected error occurs.");
            return 0;
        }
    }

    /**
     * @brief       Generate AST from token array with recursive descent parsing.
     *
     * @param[in]   const std::vector<std::string> &chs Token array from lexical analyzer
     * @return      JsonParser::Node*                   Pointer indicating the root AST node
     */
    Node* Parser(const std::vector<std::string> &chs) {
        Node* root = new Node("");
        std::cout << Value(0, chs, root) << std::endl;
        return root;
    }
}
