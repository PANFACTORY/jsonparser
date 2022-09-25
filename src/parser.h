#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <cctype>

namespace JsonParser {
    // LexicalAnalyser
    std::vector<std::string> LexicalAnalyser(std::stringstream &ss) {
        std::vector<std::string> chs;
        char ch = ss.get();
        while (!ss.eof()) {
            if (ch == ' ' || ch == '\t' || ch == '\n') {
                ch = ss.get();
                continue;
            } else if (ch == '"') {
                std::string str("\"");
                ch = ss.get();
                while (!ss.eof() && ch != ':' && ch != '}' && ch != ',' && ch != ']') {
                    str += ch;
                    ch = ss.get();
                }
                // TODO: Trim spaces at end of str.
                // TODO: Check end of str is \".
                chs.push_back(str);
            } else if (std::isdigit(ch) || ch == '-') {
                std::string str(&ch);
                ch = ss.get();
                while (!ss.eof() && ch != '}' && ch != ',' && ch != ']') {
                    str += ch;
                    ch = ss.get();
                }
                // TODO: Trim spaces at end of str.
                // TODO: str is number.
                chs.push_back(str);
            } else if (ch == 't' || ch == 'f' || ch == 'n') {
                std::string str(&ch);
                ch = ss.get();
                while (!ss.eof() && ch != '}' && ch != ',' && ch != ']') {
                    str += ch;
                    ch = ss.get();
                }
                // TODO: Trim spaces at end of str.
                // TODO: str is "true", "false" or "null".
                chs.push_back(str);
            } else {
                chs.push_back(std::string(&ch));
                ch = ss.get();
            }
        }
        return chs;
    }

    // Parser
    std::vector<std::string> Parser(std::stringstream &ss) {
        // Lexical analyse
        std::vector<std::string> chs = LexicalAnalyser(ss);

        // Parsing
        for (auto ch : chs) {
            std::cout << ch << std::endl;
        }
        return chs;
    }
}
