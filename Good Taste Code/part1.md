### 删除非空链表中的指定结点

```cpp {.line-numbers}
void remove(ListNode *&head, ListNode* entry){
// 非空单链表删除 entry 指针指向的结点，假定 entry 一定指向链表中结点
    ListNode **indirect = &head;
    while((*indirect) != entry){
        indirect = &(*indirect)->next;
    }
    *indirect = entry->next;
    delete entry;
}
```
注意这个代码还要加上虚拟头节点鲁棒性才更好