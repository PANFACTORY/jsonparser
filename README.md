# JsonParser

is a JSON parser library for C++.  
Get json data as std::istream and return the corresponding AST.  
This is a header only library.

## CI

|Status|Environment|
|:--:|:--:|
|[![CMake](https://github.com/PANFACTORY/jsonparser/actions/workflows/cmake.yml/badge.svg)](https://github.com/PANFACTORY/jsonparser/actions/workflows/cmake.yml)|ubuntu-latest(g++)|

## Generative Grammar

This library interprets sentences defined as follows as JSON.  

```
<Value> -> String | Number | Boolean | Null | <Object> | <Array>
<Object> -> "{" "}" | "{" String : <Value> {, String : <Value> } "}"  
<Array> -> [ ] | [ <Value> {, <Value>} ]
```

## Example

Create `main.cpp` and type the following code.  

```
#include <iostream>

#include "src/lexer.h"
#include "src/parser.h"

using namespace std;
using namespace JsonParser;

int main() {
    Node json = Parser(Lexer(cin));
    cout << json.Str() << endl;
    cout << json["user_info"]["user_id"].Value() << endl;
    return 0;
}
```

Build and run with the following commands(, for example, use clang++).  
Of course, set `<Your Include Path>` based on your environment.   

```
clang++ -I <Your Include Path> ./main.cpp
./a.exe
```

Enter the following in the standard input.  

```
{ "user_info": { "user_id": "A1234567", "user_name": "Yamada Taro" } } ⏎ Ctrl+z ⏎
```

Then you can get the response as below.  

```
{"user_info":{"user_id":"A1234567","user_name":"Yamada Taro"}}
A1234567
```

## Document
- [Document](https://panfactory.github.io/jsonparser/)

## Reference
- [JSON format](https://www.tohoho-web.com/ex/json.html)

## Dependency
- Google Test
- Doxygen

## License
- [MIT](https://github.com/PANFACTORY/jsonparser/blob/main/LICENSE)
