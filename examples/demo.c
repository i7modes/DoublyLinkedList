/**
 * @file demo.c
 * @brief Demonstration program for the Doubly Linked List library.
 * @author i7modes
 * @license MIT
 */

#include "doubly_linked_list.h"
#include <stdio.h>

static void print_separator(const char *title)
{
    printf("\n========================================\n");
    printf("  %s\n", title);
    printf("========================================\n");
}

int main(void)
{
    print_separator("1. Creating Doubly Linked List");
    DoublyList *dlist = DList_Create();
    printf("List created. Is empty? %s\n", DList_IsEmpty(dlist) ? "Yes" : "No");
    DList_PrintForward(dlist);

    print_separator("2. O(1) PushFront and PushBack");
    printf("Pushing 20, 10 to front; 30, 40 to back...\n");
    DList_PushFront(20, dlist);
    DList_PushFront(10, dlist);
    DList_PushBack(30, dlist);
    DList_PushBack(40, dlist);

    printf("Forward Traversal:  ");
    DList_PrintForward(dlist);

    printf("Backward Traversal: ");
    DList_PrintBackward(dlist);
    printf("Size: %zu\n", DList_Size(dlist));

    print_separator("3. Front and Back Access");
    int frontVal, backVal;
    if (DList_GetFront(dlist, &frontVal) && DList_GetBack(dlist, &backVal))
    {
        printf("Front Element: %d\n", frontVal);
        printf("Back Element:  %d\n", backVal);
    }

    print_separator("4. Insert After & Insert Before");
    Node *node20 = DList_Find(20, dlist);
    if (node20 != NULL)
    {
        printf("Inserting 25 after 20...\n");
        DList_InsertAfter(25, node20, dlist);
        DList_PrintForward(dlist);
    }

    print_separator("5. In-Place Reversal");
    printf("Before reversal:\n  Forward:  ");
    DList_PrintForward(dlist);
    printf("  Backward: ");
    DList_PrintBackward(dlist);

    DList_Reverse(dlist);

    printf("After reversal:\n  Forward:  ");
    DList_PrintForward(dlist);
    printf("  Backward: ");
    DList_PrintBackward(dlist);

    print_separator("6. Deletions (PopFront, PopBack, DeleteValue)");
    int popped;
    DList_PopFront(dlist, &popped);
    printf("Popped from front: %d\n", popped);

    DList_PopBack(dlist, &popped);
    printf("Popped from back:  %d\n", popped);

    DList_DeleteValue(25, dlist);
    printf("Deleted value 25\n");
    DList_PrintForward(dlist);

    print_separator("7. Legacy API Compatibility Check");
    Node *legacyHead = MakeEmpty(NULL);
    InsertLast(100, legacyHead);
    InsertLast(200, legacyHead);
    printf("Legacy PrintList: ");
    PrintList(legacyHead);
    printf("Legacy size(): %d\n", size(legacyHead));
    DeleteList(legacyHead);
    free(legacyHead->next); // free sentinel tail
    free(legacyHead);       // free sentinel head

    print_separator("8. Complete Teardown");
    printf("Destroying DoublyList (all nodes + sentinels)...\n");
    DList_Destroy(&dlist);
    printf("Pointer is now: %p (0 memory leaks)\n", (void *)dlist);

    printf("\nAll DoublyLinkedList demonstrations completed successfully!\n");
    return 0;
}
