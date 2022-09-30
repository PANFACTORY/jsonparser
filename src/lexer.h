/**
 * @file lexer.h
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
    inline std::vector<std::string> Lexer(std::istream& ss) {
        std::vector<std::string> chs;
        char ch = ss.get();
        while (!ss.eof()) {
            switch (ch) {
            case ' ':
            case '\f':
            case '\t':
            case '\v':
            case '\r':
            case '\n':
                ch = ss.get();
                break;
            case '"':
                {
                std::string str("\"");
                ch = ss.get();
                char pre_ch = '"';
                while (!ss.eof() && !(pre_ch != '\\' && ch == '"')) {
                    str += ch;
                    pre_ch = ch;
                    ch = ss.get();
                }
                chs.push_back(str + ch);
                if (!ss.eof()) {
                    ch = ss.get();
                }
                }
                break;
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
                {
                std::string str(&ch);
                ch = ss.get();
                while (!ss.eof() && ch != '}' && ch != ',' && ch != ']') {
                    str += ch;
                    ch = ss.get();
                }
                str = str.substr(0, str.find_last_not_of(" \f\t\v\r\n") + 1);
                if (!std::regex_match(str, std::regex("-?(0|[1-9]\\d*)(\\.\\d+)?(e[-+](0|[1-9]\\d*)(\\.\\d+)?)?"))) {
                    std::cout << str << std::endl;
                    throw std::runtime_error("At LexicalAnalyzer(): \"str\" is not a number.");
                }
                chs.push_back(str);
                }
                break;
            case 't':
            case 'f':
            case 'n':
                {
                std::string str(&ch);
                ch = ss.get();
                while (!ss.eof() && ch != '}' && ch != ',' && ch != ']') {
                    str += ch;
                    ch = ss.get();
                }
                str = str.substr(0, str.find_last_not_of(" \f\t\v\r\n") + 1);
                if (str != "true" && str != "false" && str != "null") {
                    std::cout << str << std::endl;
                    throw std::runtime_error("At LexicalAnalyzer(): \"str\" is neither true, false nor null.");
                }
                chs.push_back(str);
                }
                break;
            default:
                chs.push_back(std::string(&ch));
                ch = ss.get();
                break;
            }
        }
        return chs;
    }
}
