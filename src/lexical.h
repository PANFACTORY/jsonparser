#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cctype>

namespace JsonParser {
    // LexicalAnalyser
    std::vector<std::string> LexicalAnalyser(std::istream& ss) {
        std::vector<std::string> chs;
        char ch = ss.get();
        while (!ss.eof()) {
            if (std::isspace(ch)) {
                ch = ss.get();
                continue;
            } else if (ch == '"') {
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
            } else if (std::isdigit(ch) || ch == '-') {
                std::string str(&ch);
                ch = ss.get();
                while (!ss.eof() && ch != '}' && ch != ',' && ch != ']') {
                    str += ch;
                    ch = ss.get();
                }
                str = str.substr(0, str.find_last_not_of(" \f\t\v\r\n") + 1);
                // TODO: str is number.
                chs.push_back(str);
            } else if (ch == 't' || ch == 'f' || ch == 'n') {
                std::string str(&ch);
                ch = ss.get();
                while (!ss.eof() && ch != '}' && ch != ',' && ch != ']') {
                    str += ch;
                    ch = ss.get();
                }
                str = str.substr(0, str.find_last_not_of(" \f\t\v\r\n") + 1);
                // TODO: str is "true", "false" or "null".
                chs.push_back(str);
            } else {
                chs.push_back(std::string(&ch));
                ch = ss.get();
            }
        }
        return chs;
    }
}
