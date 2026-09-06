/**
 * @file doubly_linked_list.h
 * @brief Header file for a Doubly Linked List with Dual-Sentinel (Head & Tail) Nodes in C.
 * @author i7modes
 * @license MIT
 */

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Represents a bidirectional node in the doubly linked list.
 */
typedef struct Node {
    int data;               /**< Node payload */
    struct Node *next;      /**< Pointer to the next node */
    struct Node *prev;      /**< Pointer to the previous node */
} Node;

/**
 * @brief Container handle for the doubly linked list with head and tail sentinels.
 */
typedef struct DoublyList {
    Node *head;             /**< Sentinel head node (head->prev == NULL) */
    Node *tail;             /**< Sentinel tail node (tail->next == NULL) */
    size_t size;            /**< Cached element count for O(1) size queries */
} DoublyList;

typedef Node* Position;

/* -------------------------------------------------------------------------- */
/*                         Lifecycle & Memory Management                      */
/* -------------------------------------------------------------------------- */

/**
 * @brief Allocates and initializes a new, empty doubly linked list with head and tail sentinels.
 * @return Pointer to DoublyList, or NULL on memory allocation failure.
 */
DoublyList* DList_Create(void);

/**
 * @brief Removes and frees all payload nodes, restoring the empty invariant (head <-> tail).
 * @param list Pointer to the doubly linked list.
 */
void DList_Clear(DoublyList *list);

/**
 * @brief Completely deallocates the list, including all payload nodes and both sentinel nodes.
 * Nullifies the caller's pointer to prevent dangling references.
 * @param list_ptr Pointer to the DoublyList pointer.
 */
void DList_Destroy(DoublyList **list_ptr);

/* -------------------------------------------------------------------------- */
/*                              Query / Observers                             */
/* -------------------------------------------------------------------------- */

/**
 * @brief Checks if the list contains any payload elements.
 * @param list Pointer to the doubly linked list.
 * @return true if empty or list is NULL, false otherwise.
 */
bool DList_IsEmpty(const DoublyList *list);

/**
 * @brief Returns the number of payload elements in the list in O(1) time.
 * @param list Pointer to the doubly linked list.
 * @return Number of elements.
 */
size_t DList_Size(const DoublyList *list);

/**
 * @brief Retrieves the front element's data in O(1) time.
 * @param list Pointer to the doubly linked list.
 * @param out_val Pointer to write the value into (can be NULL).
 * @return true if found, false if list is empty.
 */
bool DList_GetFront(const DoublyList *list, int *out_val);

/**
 * @brief Retrieves the back element's data in O(1) time.
 * @param list Pointer to the doubly linked list.
 * @param out_val Pointer to write the value into (can be NULL).
 * @return true if found, false if list is empty.
 */
bool DList_GetBack(const DoublyList *list, int *out_val);

/**
 * @brief Searches for the first node containing the specified value from head to tail.
 * @param value The value to find.
 * @param list Pointer to the doubly linked list.
 * @return Pointer to the node, or NULL if not found.
 */
Node* DList_Find(int value, const DoublyList *list);

/**
 * @brief Retrieves the node at a 0-based index.
 * @param index 0-based index.
 * @param list Pointer to the doubly linked list.
 * @return Pointer to node, or NULL if out of bounds.
 */
Node* DList_GetAt(size_t index, const DoublyList *list);

/* -------------------------------------------------------------------------- */
/*                                 Insertions                                 */
/* -------------------------------------------------------------------------- */

/**
 * @brief Inserts a value at the beginning of the list in O(1) time.
 * @param value The value to insert.
 * @param list Pointer to the doubly linked list.
 * @return true on success, false on allocation failure.
 */
bool DList_PushFront(int value, DoublyList *list);

/**
 * @brief Inserts a value at the end of the list in O(1) time.
 * @param value The value to insert.
 * @param list Pointer to the doubly linked list.
 * @return true on success, false on allocation failure.
 */
bool DList_PushBack(int value, DoublyList *list);

/**
 * @brief Inserts a value immediately following a specified position node.
 * @param value The value to insert.
 * @param pos The node after which to insert (cannot be the sentinel tail).
 * @param list Pointer to the doubly linked list.
 * @return true on success, false on failure.
 */
bool DList_InsertAfter(int value, Node *pos, DoublyList *list);

/**
 * @brief Inserts a value immediately preceding a specified position node.
 * @param value The value to insert.
 * @param pos The node before which to insert (cannot be the sentinel head).
 * @param list Pointer to the doubly linked list.
 * @return true on success, false on failure.
 */
bool DList_InsertBefore(int value, Node *pos, DoublyList *list);

/* -------------------------------------------------------------------------- */
/*                                  Deletions                                 */
/* -------------------------------------------------------------------------- */

/**
 * @brief Removes the first element in O(1) time.
 * @param list Pointer to the doubly linked list.
 * @param out_val Optional pointer to receive removed value.
 * @return true on success, false if list was empty.
 */
bool DList_PopFront(DoublyList *list, int *out_val);

/**
 * @brief Removes the last element in O(1) time.
 * @param list Pointer to the doubly linked list.
 * @param out_val Optional pointer to receive removed value.
 * @return true on success, false if list was empty.
 */
bool DList_PopBack(DoublyList *list, int *out_val);

/**
 * @brief Removes a specific node in O(1) time.
 * @param node The node to remove (must not be sentinel head or tail).
 * @param list Pointer to the doubly linked list.
 * @return true on success, false if node is invalid or sentinel.
 */
bool DList_DeleteNode(Node *node, DoublyList *list);

/**
 * @brief Finds and deletes the first node containing the specified value.
 * @param value The value to remove.
 * @param list Pointer to the doubly linked list.
 * @return true if found and removed, false otherwise.
 */
bool DList_DeleteValue(int value, DoublyList *list);

/**
 * @brief Deletes the node at a given 0-based index.
 * @param index 0-based index.
 * @param list Pointer to the doubly linked list.
 * @return true on success, false if index is out of bounds.
 */
bool DList_DeleteAt(size_t index, DoublyList *list);

/* -------------------------------------------------------------------------- */
/*                           Algorithms & Utilities                           */
/* -------------------------------------------------------------------------- */

/**
 * @brief Reverses the doubly linked list in-place by swapping next and prev pointers.
 * @param list Pointer to the doubly linked list.
 */
void DList_Reverse(DoublyList *list);

/**
 * @brief Copies elements in forward order into a provided buffer.
 * @return Number of elements copied.
 */
size_t DList_ToArrayForward(const DoublyList *list, int *buffer, size_t max_len);

/**
 * @brief Copies elements in backward order into a provided buffer.
 * @return Number of elements copied.
 */
size_t DList_ToArrayBackward(const DoublyList *list, int *buffer, size_t max_len);

/**
 * @brief Prints the list visually forward:
 *        [Head] <-> [10] <-> [20] <-> [30] <-> [Tail]
 * @param list Pointer to the doubly linked list.
 */
void DList_PrintForward(const DoublyList *list);

/**
 * @brief Prints the list visually backward:
 *        [Tail] <-> [30] <-> [20] <-> [10] <-> [Head]
 * @param list Pointer to the doubly linked list.
 */
void DList_PrintBackward(const DoublyList *list);

/* -------------------------------------------------------------------------- */
/*                       Legacy API Compatibility Layer                       */
/* -------------------------------------------------------------------------- */
#define struct_node Node

static inline Node* MakeEmpty(Node *head) {
    (void)head;
    Node *h = (Node *)malloc(sizeof(Node));
    Node *t = (Node *)malloc(sizeof(Node));
    if (h == NULL || t == NULL) return NULL;
    h->data = 0; h->next = t; h->prev = NULL;
    t->data = 0; t->next = NULL; t->prev = h;
    return h;
}

static inline int IsEmpty(Node *L) {
    return (L == NULL || L->next == NULL || L->next->next == NULL) ? 1 : 0;
}

static inline int IsLast(Node *P, Node *L) {
    (void)L;
    return (P != NULL && P->next != NULL && P->next->next == NULL) ? 1 : 0;
}

static inline Node* Find(int X, Node *L) {
    if (L == NULL) return NULL;
    Node *P = L->next;
    while (P != NULL && P->next != NULL && P->data != X) P = P->next;
    return (P != NULL && P->next != NULL) ? P : NULL;
}

static inline Node* FindPrevious(int X, Node *L) {
    if (L == NULL) return NULL;
    Node *P = L->next;
    while (P != NULL && P->next != NULL && P->data != X) P = P->next;
    return (P != NULL) ? P->prev : NULL;
}

static inline void Delete(int X, Node *L) {
    Node *P = Find(X, L);
    if (P != NULL) {
        P->prev->next = P->next;
        P->next->prev = P->prev;
        free(P);
    }
}

static inline void Insert(int X, Node *head, Node *tail, Node *P) {
    (void)head; (void)tail;
    if (P == NULL) return;
    Node *temp = (Node *)malloc(sizeof(Node));
    if (temp == NULL) return;
    temp->data = X;
    temp->next = P->next;
    temp->prev = P;
    if (P->next != NULL) P->next->prev = temp;
    P->next = temp;
}

static inline void InsertLast(int X, Node *L) {
    if (L == NULL) return;
    Node *tail = L;
    while (tail->next != NULL) tail = tail->next;
    // tail is the sentinel tail; insert before it
    Insert(X, L, tail, tail->prev);
}

static inline void PrintList(Node *L) {
    if (L == NULL || IsEmpty(L)) {
        printf("Empty list\n");
        return;
    }
    Node *P = L->next;
    while (P != NULL && P->next != NULL) {
        printf("%d\t", P->data);
        P = P->next;
    }
    printf("\n");
}

static inline void DeleteList(Node *L) {
    if (L == NULL) return;
    Node *P = L->next;
    while (P != NULL && P->next != NULL) {
        Node *temp = P->next;
        free(P);
        P = temp;
    }
    if (P != NULL) {
        L->next = P;
        P->prev = L;
    }
}

static inline int size(Node *L) {
    if (L == NULL) return 0;
    Node *P = L->next;
    int count = 0;
    while (P != NULL && P->next != NULL) {
        count++;
        P = P->next;
    }
    return count;
}

#ifdef __cplusplus
}
#endif

#endif /* DOUBLY_LINKED_LIST_H */
