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
    std::vector<std::string> LexicalAnalyzer(std::istream& ss) {
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
                // TODO: "で閉じているかで判別する
                while (!ss.eof() && ch != ':' && ch != '}' && ch != ',' && ch != ']') {
                    str += ch;
                    ch = ss.get();
                }
                str = str.substr(0, str.find_last_not_of(" \f\t\v\r\n") + 1);
                // TODO: Check end of str is \".
                chs.push_back(str);
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
