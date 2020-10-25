#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 1024

#define GetValue(node) (node->data)
#define NextNode(node) (node->next)
#define PrevNode(node) (node->prev)
#define RemoveList(list) (RemoveNodes(list.first))

/* リストの要素 (ノード) を表す構造体 */
typedef struct tagListNode {
    struct tagListNode *prev;     /* 前の要素へのポインタ */
    struct tagListNode *next;     /* 次の要素へのポインタ */

    int data;                     /* この要素が持つデータ */
} ListNode;

// リストの構造体
typedef struct tagList {
    ListNode
        *first, // 最初
        *last;  // 最後
} List;

/*----------
@brief: set value of a node.
@arg:
    node:  the target node
    value: setting value
@return: pointer of the node.
----------*/
ListNode *SetValue(ListNode *node, int value) {
    GetValue(node) = value;
    return node;
}

/*----------
@brief: open memory of nodes after. recursing.
@arg:
    node: the beggning node
@return: NULL if the node is the end, else pointer of the next node.
----------*/
ListNode *RemoveNodes(ListNode *node) {
    if (node == NULL) return NULL;

    ListNode *next = RemoveNodes(NextNode(node));
    free(node);
    return next;
}

/*----------
@brief: create new node.
@arg:
    data: value of new node
@return: pointer of the created node.
----------*/
ListNode *CreateNewNode(int data) {
    ListNode *newnode;
    newnode = (ListNode*)malloc(sizeof(ListNode));
    NextNode(newnode) = PrevNode(newnode) = NULL;
    SetValue(newnode, data);
    return newnode;
}

/*----------
@brief: append new node to the node.
@arg:
    node: the target node
    newnode: adding node
@return: pointer of the new node.
----------*/
ListNode *AppendNode(ListNode *node, ListNode *newnode) {
    if (node != NULL) {
        NextNode(newnode) = NextNode(node);
        PrevNode(newnode) = node;
        NextNode(node) = newnode;
    }

    return newnode;
}

/*----------
@brief: insert a node before a node.
@arg:
    node1: the target node
    node2: node that'll be inserted
@return: pointer of the inserted node
----------*/
ListNode *InsertNode(ListNode *node1, ListNode *node2) {
    PrevNode(node2) = PrevNode(node1);
    NextNode(PrevNode(node2)) = node2;
    NextNode(node2) = node1;
    PrevNode(node1) = node2;

    return node2;
}

/*----------
@brief: insert another list before a node.
@arg:
    node: the target node
    list: list that'll be inserted
@return: first node's pointer of the inserted list
----------*/
List InsertNodes(ListNode *node, List list) {
    PrevNode(list.first) = PrevNode(node);
    NextNode(PrevNode(node)) = list.first;
    NextNode(list.last) = node;
    PrevNode(node) = list.last;

    return list;
}

/*----------
@brief: pop a node after a node.
@arg:
    node: the target node
@return: pointer of the popped node
----------*/
ListNode *PopNode(ListNode *node) {
    ListNode *next = NextNode(node);

    if (NextNode(NextNode(node))) PrevNode(NextNode(NextNode(node))) = node;
    NextNode(node) = NextNode(NextNode(node));

    PrevNode(next) = NextNode(next) = NULL;

    return next;
}

/*----------
@brief: pop a list after a node.
@arg:
    node: the target node
    size: size of popping list
@return: first node's pointer of the popped list
----------*/
List PopNodes(ListNode *node, int size) {
    List list;
    list.first = NextNode(node);

    ListNode *now = PrevNode(list.first);
    while (size-- && now) now = NextNode(now);
    list.last = now;

    if (NextNode(NextNode(list.last))) PrevNode(NextNode(NextNode(list.last))) = node;
    if (NextNode(list.last)) NextNode(node) = NextNode(list.last);
    PrevNode(NextNode(list.last)) = node;

    PrevNode(list.first) = NextNode(list.last) = NULL;

    return list;
}

int main() {
    int      buf, sum = 0;
    ListNode *now, *newnode;
    List     list;
    char     buffer[MAXLENGTH];

    list.first = list.last = NULL;

    do {
        printf("整数を入力してください (何も入力しないと終了): ");
        fgets(buffer, MAXLENGTH, stdin);
        sscanf(buffer, "%d", &buf);

        if (strlen(buffer) < 2) continue;

        newnode = CreateNewNode(buf);

        list.last = AppendNode(list.last, newnode);

        if (list.first == NULL) list.first = list.last;
    } while (strlen(buffer) > 1);

    /* 合計値を算出 */
    printf("--入力されたのは以下の数です--\n");
    for (now = list.first; now != NULL; now = NextNode(now)) {
        printf("%d\t", GetValue(now));
        sum += GetValue(now);
    }
    printf("\n----\n以上の数の合計値は%dです．\n", sum);

    List newlist;
    newlist.first = CreateNewNode(100);
    newlist.last  = AppendNode(newlist.first, CreateNewNode(100));

    InsertNodes(list.last, newlist);
    for (now = list.first; now != NULL; now = NextNode(now)) {
        printf("%d\t", GetValue(now));
    }
    puts("");

    PopNodes(NextNode(list.first), 2);
    for (now = list.first; now != NULL; now = NextNode(now)) {
        printf("%d\t", GetValue(now));
    }
    puts("");

    RemoveList(list);
    return EXIT_SUCCESS;
}
