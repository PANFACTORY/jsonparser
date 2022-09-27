# JsonParser

C++言語のためのJSONパーサーライブラリです。

## JSON

```
<Value> -> [String] | [Number] | [Boolean] | [Null] | <Object> | <Array>
<Object> -> "{" "}" | "{" [String]: <Value> {, [String]: <Value> } "}"  
<Array> -> "[" "]" | "[" <Value> {, <Value>} "]"
```

## ドキュメント
- [ドキュメント](https://panfactory.github.io/jsonparser/html)

## 参考URL
- [JSON形式](https://www.tohoho-web.com/ex/json.html)

## 依存
- Google Test
- Doxygen
