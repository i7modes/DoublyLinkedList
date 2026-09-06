/**
 * @file doubly_linked_list.c
 * @brief Implementation of Doubly Linked List with Dual-Sentinel Nodes.
 * @author i7modes
 * @license MIT
 */

#include "doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

/* -------------------------------------------------------------------------- */
/*                         Lifecycle & Memory Management                      */
/* -------------------------------------------------------------------------- */

DoublyList* DList_Create(void)
{
    DoublyList *list = (DoublyList *)malloc(sizeof(DoublyList));
    if (list == NULL)
    {
        fprintf(stderr, "Error: Out of memory in DList_Create (list handle).\n");
        return NULL;
    }

    Node *head = (Node *)malloc(sizeof(Node));
    Node *tail = (Node *)malloc(sizeof(Node));

    if (head == NULL || tail == NULL)
    {
        fprintf(stderr, "Error: Out of memory in DList_Create (sentinels).\n");
        free(head);
        free(tail);
        free(list);
        return NULL;
    }

    head->data = 0;
    head->prev = NULL;
    head->next = tail;

    tail->data = 0;
    tail->next = NULL;
    tail->prev = head;

    list->head = head;
    list->tail = tail;
    list->size = 0;

    return list;
}

void DList_Clear(DoublyList *list)
{
    if (list == NULL || list->head == NULL || list->tail == NULL)
    {
        return;
    }

    Node *current = list->head->next;
    while (current != list->tail)
    {
        Node *temp = current->next;
        free(current);
        current = temp;
    }

    /* Restore empty sentinel invariant */
    list->head->next = list->tail;
    list->tail->prev = list->head;
    list->size = 0;
}

void DList_Destroy(DoublyList **list_ptr)
{
    if (list_ptr == NULL || *list_ptr == NULL)
    {
        return;
    }

    DoublyList *list = *list_ptr;
    DList_Clear(list);

    if (list->head != NULL)
    {
        free(list->head);
    }
    if (list->tail != NULL)
    {
        free(list->tail);
    }

    free(list);
    *list_ptr = NULL;
}

/* -------------------------------------------------------------------------- */
/*                              Query / Observers                             */
/* -------------------------------------------------------------------------- */

bool DList_IsEmpty(const DoublyList *list)
{
    if (list == NULL || list->head == NULL || list->tail == NULL)
    {
        return true;
    }
    return (list->head->next == list->tail);
}

size_t DList_Size(const DoublyList *list)
{
    return (list != NULL) ? list->size : 0;
}

bool DList_GetFront(const DoublyList *list, int *out_val)
{
    if (DList_IsEmpty(list))
    {
        return false;
    }

    if (out_val != NULL)
    {
        *out_val = list->head->next->data;
    }
    return true;
}

bool DList_GetBack(const DoublyList *list, int *out_val)
{
    if (DList_IsEmpty(list))
    {
        return false;
    }

    if (out_val != NULL)
    {
        *out_val = list->tail->prev->data;
    }
    return true;
}

Node* DList_Find(int value, const DoublyList *list)
{
    if (list == NULL || list->head == NULL || list->tail == NULL)
    {
        return NULL;
    }

    Node *current = list->head->next;
    while (current != list->tail)
    {
        if (current->data == value)
        {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

Node* DList_GetAt(size_t index, const DoublyList *list)
{
    if (list == NULL || index >= list->size)
    {
        return NULL;
    }

    /* Optimization: Traverse from head if index is in first half, else from tail */
    if (index < list->size / 2)
    {
        Node *current = list->head->next;
        for (size_t i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current;
    }
    else
    {
        Node *current = list->tail->prev;
        for (size_t i = list->size - 1; i > index; i--)
        {
            current = current->prev;
        }
        return current;
    }
}

/* -------------------------------------------------------------------------- */
/*                                 Insertions                                 */
/* -------------------------------------------------------------------------- */

bool DList_PushFront(int value, DoublyList *list)
{
    if (list == NULL)
    {
        return false;
    }
    return DList_InsertAfter(value, list->head, list);
}

bool DList_PushBack(int value, DoublyList *list)
{
    if (list == NULL)
    {
        return false;
    }
    return DList_InsertBefore(value, list->tail, list);
}

bool DList_InsertAfter(int value, Node *pos, DoublyList *list)
{
    if (list == NULL || pos == NULL || pos == list->tail)
    {
        return false;
    }

    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        fprintf(stderr, "Error: Out of memory in DList_InsertAfter.\n");
        return false;
    }

    newNode->data = value;
    newNode->next = pos->next;
    newNode->prev = pos;

    pos->next->prev = newNode;
    pos->next = newNode;

    list->size++;
    return true;
}

bool DList_InsertBefore(int value, Node *pos, DoublyList *list)
{
    if (list == NULL || pos == NULL || pos == list->head)
    {
        return false;
    }

    return DList_InsertAfter(value, pos->prev, list);
}

/* -------------------------------------------------------------------------- */
/*                                  Deletions                                 */
/* -------------------------------------------------------------------------- */

bool DList_PopFront(DoublyList *list, int *out_val)
{
    if (DList_IsEmpty(list))
    {
        return false;
    }

    Node *first = list->head->next;
    if (out_val != NULL)
    {
        *out_val = first->data;
    }

    return DList_DeleteNode(first, list);
}

bool DList_PopBack(DoublyList *list, int *out_val)
{
    if (DList_IsEmpty(list))
    {
        return false;
    }

    Node *last = list->tail->prev;
    if (out_val != NULL)
    {
        *out_val = last->data;
    }

    return DList_DeleteNode(last, list);
}

bool DList_DeleteNode(Node *node, DoublyList *list)
{
    if (list == NULL || node == NULL || node == list->head || node == list->tail)
    {
        return false;
    }

    node->prev->next = node->next;
    node->next->prev = node->prev;

    free(node);
    list->size--;
    return true;
}

bool DList_DeleteValue(int value, DoublyList *list)
{
    Node *node = DList_Find(value, list);
    if (node == NULL)
    {
        return false;
    }

    return DList_DeleteNode(node, list);
}

bool DList_DeleteAt(size_t index, DoublyList *list)
{
    Node *node = DList_GetAt(index, list);
    if (node == NULL)
    {
        return false;
    }

    return DList_DeleteNode(node, list);
}

/* -------------------------------------------------------------------------- */
/*                           Algorithms & Utilities                           */
/* -------------------------------------------------------------------------- */

void DList_Reverse(DoublyList *list)
{
    if (list == NULL || list->size <= 1)
    {
        return;
    }

    Node *current = list->head;
    while (current != NULL)
    {
        Node *temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        current = temp;
    }

    /* Swap head and tail pointers */
    Node *temp_head = list->head;
    list->head = list->tail;
    list->tail = temp_head;
}

size_t DList_ToArrayForward(const DoublyList *list, int *buffer, size_t max_len)
{
    if (list == NULL || buffer == NULL || max_len == 0)
    {
        return 0;
    }

    size_t count = 0;
    const Node *current = list->head->next;

    while (current != list->tail && count < max_len)
    {
        buffer[count++] = current->data;
        current = current->next;
    }

    return count;
}

size_t DList_ToArrayBackward(const DoublyList *list, int *buffer, size_t max_len)
{
    if (list == NULL || buffer == NULL || max_len == 0)
    {
        return 0;
    }

    size_t count = 0;
    const Node *current = list->tail->prev;

    while (current != list->head && count < max_len)
    {
        buffer[count++] = current->data;
        current = current->prev;
    }

    return count;
}

void DList_PrintForward(const DoublyList *list)
{
    if (list == NULL)
    {
        printf("(null)\n");
        return;
    }

    if (DList_IsEmpty(list))
    {
        printf("[Head] <-> [Tail] (empty)\n");
        return;
    }

    printf("[Head]");
    const Node *current = list->head->next;

    while (current != list->tail)
    {
        printf(" <-> [%d]", current->data);
        current = current->next;
    }

    printf(" <-> [Tail]\n");
}

void DList_PrintBackward(const DoublyList *list)
{
    if (list == NULL)
    {
        printf("(null)\n");
        return;
    }

    if (DList_IsEmpty(list))
    {
        printf("[Tail] <-> [Head] (empty)\n");
        return;
    }

    printf("[Tail]");
    const Node *current = list->tail->prev;

    while (current != list->head)
    {
        printf(" <-> [%d]", current->data);
        current = current->prev;
    }

    printf(" <-> [Head]\n");
}
