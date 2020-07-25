## 作答

- `FuncA` 作用是 `(e)` 建立新節點，內容是 value，並安插在結尾
- `FuncB` 作用是 `(d)` 建立新節點，內容是 value，並安插在開頭
- `FuncC` 作用是 `(e)` 找到節點內容為 value2 的節點，並在之後插入新節點，內容為 value1

在幫 malloc 前面做 type cast `(struct node*)` 之後方可執行，輸出以下

```
Traversal in forward direction
48 51 63 72 86
Traversal in reverse direction
86 72 63 51 48
```
