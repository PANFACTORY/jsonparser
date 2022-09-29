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
    /**
     * @brief       Generate AST from token array with recursive descent parsing.
     *
     * @param[in]   const std::vector<std::string> &chs Token array from lexical analyzer
     * @return      JsonParser::Node*                   Pointer indicating the root AST node
     */
    Node* Parser(const std::vector<std::string> &chs);
}
