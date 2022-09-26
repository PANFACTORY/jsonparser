#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <cctype>

#include "lexical.h"

namespace JsonParser {
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
