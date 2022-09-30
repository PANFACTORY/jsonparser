cmake_minimum_required(VERSION 3.24)

project(jsonparser_test CXX)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.0.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(JsonParserTest test/node_test.cpp test/lexer_test.cpp test/parser_test.cpp)
target_link_libraries(JsonParserTest gtest_main)

include(GoogleTest)
gtest_discover_tests(JsonParserTest)
