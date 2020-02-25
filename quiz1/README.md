# Linked-list Sorting

## 1. 解釋上述程式運作原理

First of all we shall notice that the sorting is in a form of right recursion. Recursively the function returns the `start` of sorted linked-list. So we have `left` and `right` as a sorted list. Then in the next for-loop, our goal is to merge list `left` and `right` together into 1 sorted list. The variable `merge` stands for the current end-point of the merged list. Assuming the `merge` list to be a sorted list, and knowing that `left` and `right` is sorted, we can obtain the list in `O(n)` by comparing the front of both lists and insert the smaller one to `merge`, then "`pop`" the small element from the list and continue on comparing with the next element of the list. The comparison will end until both lists are all inserted into list `merge`, and therefore we have the result.

## 2. 指出程式改進空間，特別是考慮到 [Optimizing merge sort](https://en.wikipedia.org/wiki/Merge_sort#Optimizing_merge_sort)

Since list `left` always contain only 1 element. (We restricted that with `LL0`) So starting from the rightmost element of the data, we will have them sorted and go all the way back to the beginning. With every for-loop taking exactly the sum of elements from `left` and `right` comparisons. We have a `time complexity O(n^2)` sorting algorithm. As we take account for the space complexity, only local variables to record head and tails of the list is used, so the space complexity if `O(n)`.

We can obtain size of the list and the middle element in `O(n)` time. As we can divide the list in half, we now have `left` and `right` with approximately equal size. We can fo sorting them as `left` and `right`, then do the merging. This algorithm takes `O(n log n)`.  For the whole list we can at most divide it `O(log n)` times. And we merge 2 lists together each time. So we have a `O(n log n)` sorting algorithm. In the improved version no data is copied so the space complexity remains `O(n)`.

## 3. 將上述 singly-linked list 擴充為 circular doubly-linked list 並重新實作對應的 sort

##### Modified structure

```
typedef struct __list {
    int data;
    struct __list *next;
    struct __list *prev;
} list;
```

❗️ Beware to maintain circular of the linked-list.

## 4. 依循 Linux 核心 [include/linux/list.h](https://github.com/torvalds/linux/blob/master/include/linux/list.h) 程式碼的方式，改寫上述排序程式

TODO

## 5. 嘗試將原本遞迴的程式改寫為 iterative 版本;

It would be easy to modify the code to iterative version. We are actually doing the `merge` action with increasing chunk size to the given linked-list. However, the constraint of linked-list is that the access time of a certain pointer (element) will take `O(n)` time. If we don't create an array to record the elements we will need `O(n^2 log n)` time. Creating array doubles the memory usage, although the space complexity remains the same, but when size of the list is larger than size of the main memory, there will occur several disk I/O since the list cannot be filled completely into the memory.

