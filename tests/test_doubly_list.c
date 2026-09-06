/**
 * @file test_doubly_list.c
 * @brief Automated unit test suite for Doubly Linked List with bidirectional invariant checks.
 * @author i7modes
 * @license MIT
 */

#include "doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static int total_tests = 0;
static int passed_tests = 0;

#define TEST_ASSERT(expr, msg) do { \
    total_tests++; \
    if (expr) { \
        passed_tests++; \
        printf("  [PASS] %s\n", msg); \
    } else { \
        printf("  [FAIL] %s (Line %d)\n", msg, __LINE__); \
    } \
} while (0)

/**
 * @brief Helper that verifies every node's next->prev and prev->next match.
 */
static bool verify_bidirectional_integrity(const DoublyList *list)
{
    if (list == NULL || list->head == NULL || list->tail == NULL)
    {
        return false;
    }

    if (list->head->prev != NULL || list->tail->next != NULL)
    {
        return false;
    }

    const Node *curr = list->head;
    size_t count = 0;

    while (curr != list->tail)
    {
        if (curr->next == NULL)
        {
            return false;
        }
        if (curr->next->prev != curr)
        {
            return false;
        }
        curr = curr->next;
        if (curr != list->tail)
        {
            count++;
        }
    }

    return (count == list->size);
}

static void test_initialization(void)
{
    printf("\n--- Test: Initialization & Sentinels ---\n");
    DoublyList *list = DList_Create();
    TEST_ASSERT(list != NULL, "DList_Create returns non-NULL");
    TEST_ASSERT(DList_IsEmpty(list) == true, "New list is empty");
    TEST_ASSERT(DList_Size(list) == 0, "New list size is 0");
    TEST_ASSERT(verify_bidirectional_integrity(list) == true, "Empty list passes bidirectional integrity");

    DList_Destroy(&list);
    TEST_ASSERT(list == NULL, "DList_Destroy nullifies pointer");
}

static void test_push_and_bidirectional_traversal(void)
{
    printf("\n--- Test: Push & Traversal Order ---\n");
    DoublyList *list = DList_Create();

    DList_PushBack(20, list);
    DList_PushBack(30, list);
    DList_PushFront(10, list); // [10, 20, 30]

    TEST_ASSERT(DList_Size(list) == 3, "Size is 3");
    TEST_ASSERT(verify_bidirectional_integrity(list) == true, "Integrity verified after pushes");

    int fwd[3];
    int bwd[3];
    DList_ToArrayForward(list, fwd, 3);
    DList_ToArrayBackward(list, bwd, 3);

    TEST_ASSERT(fwd[0] == 10 && fwd[1] == 20 && fwd[2] == 30, "Forward order matches: 10, 20, 30");
    TEST_ASSERT(bwd[0] == 30 && bwd[1] == 20 && bwd[2] == 10, "Backward order matches: 30, 20, 10");

    int frontVal, backVal;
    TEST_ASSERT(DList_GetFront(list, &frontVal) && frontVal == 10, "GetFront returns 10");
    TEST_ASSERT(DList_GetBack(list, &backVal) && backVal == 30, "GetBack returns 30");

    DList_Destroy(&list);
}

static void test_insert_after_and_before(void)
{
    printf("\n--- Test: InsertAfter & InsertBefore ---\n");
    DoublyList *list = DList_Create();
    DList_PushBack(10, list);
    DList_PushBack(30, list);

    Node *node10 = DList_Find(10, list);
    TEST_ASSERT(node10 != NULL, "Found node 10");

    DList_InsertAfter(20, node10, list); // [10, 20, 30]
    TEST_ASSERT(DList_Size(list) == 3, "Size is 3 after InsertAfter");
    TEST_ASSERT(verify_bidirectional_integrity(list) == true, "Integrity verified after InsertAfter");

    Node *node30 = DList_Find(30, list);
    DList_InsertBefore(25, node30, list); // [10, 20, 25, 30]
    TEST_ASSERT(DList_Size(list) == 4, "Size is 4 after InsertBefore");
    TEST_ASSERT(verify_bidirectional_integrity(list) == true, "Integrity verified after InsertBefore");

    Node *node25 = DList_GetAt(2, list);
    TEST_ASSERT(node25 != NULL && node25->data == 25, "GetAt(2) returns node 25");

    DList_Destroy(&list);
}

static void test_deletions(void)
{
    printf("\n--- Test: Deletions (PopFront, PopBack, DeleteValue, DeleteAt) ---\n");
    DoublyList *list = DList_Create();
    DList_PushBack(1, list);
    DList_PushBack(2, list);
    DList_PushBack(3, list);
    DList_PushBack(4, list);
    DList_PushBack(5, list); // [1, 2, 3, 4, 5]

    int popped;
    TEST_ASSERT(DList_PopFront(list, &popped) && popped == 1, "PopFront returns 1");
    TEST_ASSERT(DList_Size(list) == 4, "Size is 4");
    TEST_ASSERT(verify_bidirectional_integrity(list) == true, "Integrity verified after PopFront");

    TEST_ASSERT(DList_PopBack(list, &popped) && popped == 5, "PopBack returns 5");
    TEST_ASSERT(DList_Size(list) == 3, "Size is 3");
    TEST_ASSERT(verify_bidirectional_integrity(list) == true, "Integrity verified after PopBack");

    // Delete value 3 (middle)
    TEST_ASSERT(DList_DeleteValue(3, list) == true, "DeleteValue(3) returns true");
    TEST_ASSERT(DList_Size(list) == 2, "Size is 2");
    TEST_ASSERT(DList_Find(3, list) == NULL, "Value 3 no longer found");
    TEST_ASSERT(verify_bidirectional_integrity(list) == true, "Integrity verified after DeleteValue");

    // Delete at index 0 (now 2)
    TEST_ASSERT(DList_DeleteAt(0, list) == true, "DeleteAt(0) returns true");
    TEST_ASSERT(DList_Size(list) == 1, "Size is 1");
    TEST_ASSERT(DList_GetAt(0, list)->data == 4, "Only remaining element is 4");
    TEST_ASSERT(verify_bidirectional_integrity(list) == true, "Integrity verified after DeleteAt");

    // Pop the last remaining
    TEST_ASSERT(DList_PopFront(list, &popped) && popped == 4, "PopFront last item returns 4");
    TEST_ASSERT(DList_IsEmpty(list) == true, "List is now empty");
    TEST_ASSERT(verify_bidirectional_integrity(list) == true, "Empty list integrity verified");

    // Pop on empty returns false
    TEST_ASSERT(DList_PopFront(list, &popped) == false, "PopFront on empty returns false");
    TEST_ASSERT(DList_PopBack(list, &popped) == false, "PopBack on empty returns false");

    DList_Destroy(&list);
}

static void test_reversal(void)
{
    printf("\n--- Test: In-Place Reversal ---\n");
    DoublyList *list = DList_Create();

    // Reverse empty list
    DList_Reverse(list);
    TEST_ASSERT(DList_IsEmpty(list) == true, "Reversing empty list is safe");
    TEST_ASSERT(verify_bidirectional_integrity(list) == true, "Integrity intact on reversed empty list");

    // Reverse 1 item list
    DList_PushBack(42, list);
    DList_Reverse(list);
    int val;
    DList_GetFront(list, &val);
    TEST_ASSERT(val == 42, "Reversing single item list preserves item");
    TEST_ASSERT(verify_bidirectional_integrity(list) == true, "Integrity intact on reversed 1-item list");

    // Multi-element reversal
    DList_PushBack(43, list);
    DList_PushBack(44, list);
    DList_PushBack(45, list); // [42, 43, 44, 45]

    DList_Reverse(list); // Should be [45, 44, 43, 42]
    TEST_ASSERT(verify_bidirectional_integrity(list) == true, "Integrity verified after reversal");

    int fwd[4];
    DList_ToArrayForward(list, fwd, 4);
    TEST_ASSERT(fwd[0] == 45 && fwd[1] == 44 && fwd[2] == 43 && fwd[3] == 42,
                "Forward array matches reversed order (45, 44, 43, 42)");

    int bwd[4];
    DList_ToArrayBackward(list, bwd, 4);
    TEST_ASSERT(bwd[0] == 42 && bwd[1] == 43 && bwd[2] == 44 && bwd[3] == 45,
                "Backward array matches original order (42, 43, 44, 45)");

    DList_Destroy(&list);
}

int main(void)
{
    printf("========================================\n");
    printf("  Doubly Linked List Automated Tests\n");
    printf("========================================\n");

    test_initialization();
    test_push_and_bidirectional_traversal();
    test_insert_after_and_before();
    test_deletions();
    test_reversal();

    printf("\n========================================\n");
    printf("  Results: %d/%d assertions passed\n", passed_tests, total_tests);
    printf("========================================\n");

    return (passed_tests == total_tests) ? 0 : 1;
}
