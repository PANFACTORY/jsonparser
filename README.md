# JsonParser

C++言語のためのJSONパーサーライブラリです。

## JSON

```
<Json> -> "{" { <Pair> | <Pair>, } "}"
<Pair> -> <Key>: <Value>
<Key> -> "<Alp> { <Alp> | <Num> } "
<Value> -> "<Alp> { <Alp> | <Num> } "
<Alp> -> a|...|z|A|...|Z
<Num> -> 0|...|9
```

## 参考URL
- [JSON形式](https://www.tohoho-web.com/ex/json.html)
