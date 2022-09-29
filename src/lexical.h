/**
 * @file lexical.h
 * @author PANFACTORY (github.com/PANFACTORY)
 * @brief Lexical analyzer of JSON
 * @version 0.1
 * @date 2022-09-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cctype>
#include <regex>

namespace JsonParser {
    /**
     * @brief       Lexical analyze JSON format stream and generate token array.
     *
     * @param[in]   std::istream& ss            JSON format stream
     * @return      std::vector<std::string>    Token array
     */
    std::vector<std::string> LexicalAnalyzer(std::istream& ss);
}
