#include <stddef.h>
struct node {
    int data;
    struct node *next;
} *head;

void insert(struct node *newt)
{
    struct node **link = &head;
    while (*link && (*link)->data < newt->data)
        link = &(*link)->next;
    newt->next = *link;
    *link = newt;
}
/*
然而在 Linus Travold 的 TED Talk 上，
他有分享一段 Linux 中是如何實作 Linux 中是如何實作 linked-list 的插入。
使用了 pointer-to-pointer 來移動物件。為什麼要這樣做呢？

上面較拙劣的作法是把串列當作物件來考慮。
但是在「插入」這件事情，我們可以往他的本質去想，我們要執行兩部：

1. 找到物件 `obj`
2. 把新物件 `newt` 插在 `obj` 之前

pointer 是指向實際資料的地址，
而 pointer to pointer 是指向儲存 pointer 這段資料的地址。
改變 `*link` 內容時，原本 pointer 中儲存的資料仍然存在，已經被上一行 `newt->next = *link` 串起來。
*/