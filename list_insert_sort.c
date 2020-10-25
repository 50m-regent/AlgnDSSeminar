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

    if (PrevNode(node1)) NextNode(PrevNode(node1)) = node2;
    NextNode(node2) = node1;
    PrevNode(node1) = node2;

    return node2;
}

/*----------
@brief: pop a node.
@arg:
    node: target node
@return: pointer of the popped node
----------*/
ListNode *PopNode(ListNode *node) {
    if (NextNode(node)) PrevNode(NextNode(node)) = PrevNode(node);
    if (PrevNode(node)) NextNode(PrevNode(node)) = NextNode(node);

    PrevNode(node) = NextNode(node) = NULL;

    return node;
}

/*----------
@brief: insert sort of list
@arg:
    list: sorting list
@return:
----------*/
void InsertSort(ListNode **fnode, ListNode **lnode) {
    ListNode
        *sorted, // edge node in list where it is sorted til there
        *now,    // node that we are looking at
        *next;   // next sorting node

    // while list is not sorted
    for (sorted = *fnode; NextNode(sorted);) {
        next = NextNode(sorted);
        
        // search the inserting place
        for (now = *fnode; now != next; now = NextNode(now)) {
            if (GetValue(now) > GetValue(next)) break;
        }
        if (now == next) {
            sorted = next;
            continue;
        }

        // when a node is popped from last place
        if (next == *lnode) lnode = &sorted;

        PopNode(next);
        InsertNode(now, next);

        // then a node is inserted to first place
        if (now == *fnode) fnode = &next;
    }
}

int main() {
    int      buf;
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

    printf("--入力されたのは以下の数です--\n");
    for (now = list.first; now; now = NextNode(now)) {
        printf("%d\t", GetValue(now));
    }
    puts("");

    InsertSort(&list.first, &list.last);

    puts("--ソートしました--");
    for (now = list.first; now; now = NextNode(now)) {
        printf("%d\t", GetValue(now));
    }
    puts("");

    RemoveList(list);
    return EXIT_SUCCESS;
}
