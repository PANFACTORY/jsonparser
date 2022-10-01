# JsonParser

C++言語のためのJSONパーサーライブラリです。  
std::istreamでJSONデータを受け取り、対応する抽象構文木を生成します。

## CI

|状態|環境|
|:--:|:--:|
|[![CMake](https://github.com/PANFACTORY/jsonparser/actions/workflows/cmake.yml/badge.svg)](https://github.com/PANFACTORY/jsonparser/actions/workflows/cmake.yml)|ubuntu-latest(g++)|

## 生成規則

このライブラリではJSONフォーマットが以下の生成規則に従うものと想定します。

```
<Value> -> String | Number | Boolean | Null | <Object> | <Array>
<Object> -> "{" "}" | "{" String : <Value> {, String : <Value> } "}"  
<Array> -> [ ] | [ <Value> {, <Value>} ]
```

## サンプル

`main.cpp`を作成して以下のコードを入力します。

```
#include <iostream>

#include "src/lexer.h"
#include "src/parser.h"

using namespace std;
using namespace JsonParser;

int main() {
    cout << Parser(Lexer(cin))->Str() << std::endl;
    return 0;
}
```

例えばWindowsでClangを用いる場合、以下のコマンドでビルド、実行します。  
なお、`<Your Include Path>`は使用される環境に合わせて設定してください。

```
clang++ -I <Your Include Path> ./main.cpp
./a.exe
```

標準入力で以下を入力し、続けて⏎、Ctrl+z、⏎を入力します。

```
{ "user_info": { "user_id": "A1234567", "user_name": "Yamada Taro" } }
```

すると、以下の結果が返されます。

```
{"user_info":{"user_id":"A1234567","user_name":"Yamada Taro"}}
```

## ドキュメント
- [ドキュメント](https://panfactory.github.io/jsonparser/)

## 参考URL
- [JSON形式](https://www.tohoho-web.com/ex/json.html)

## 依存
- Google Test
- Doxygen
