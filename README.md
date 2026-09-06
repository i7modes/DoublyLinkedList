# Doubly Linked List in C (Dual-Sentinel Architecture)

[![CI](https://github.com/i7modes/DoublyLinkedList/actions/workflows/ci.yml/badge.svg)](https://github.com/i7modes/DoublyLinkedList/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![C Standard](https://img.shields.io/badge/C-C99-blue.svg)
![Memory Status](https://img.shields.io/badge/Valgrind-0%20Leaks-brightgreen.svg)

A high-performance, production-ready implementation of a **Doubly Linked List** in C99 featuring a **Dual-Sentinel (Head & Tail)** architecture. Includes bidirectional traversals, $\mathcal{O}(1)$ push/pop operations at both ends, in-place reversal, automated test suite with invariant checks, and zero memory leaks.

---

## Architecture: Dual-Sentinel Pattern

This implementation employs both a **Sentinel Head** and a **Sentinel Tail** node bounding the list. Neither sentinel holds application data.

```text
         +-------------------+         +-------------------+         +-------------------+
NULL <-- |   Sentinel Head   | <=====> |   Payload Node    | <=====> |   Sentinel Tail   | --> NULL
         | [prev:0 | next:*] |         | [prev:* | next:*] |         | [prev:* | next:0] |
         +-------------------+         +-------------------+         +-------------------+
```

### Why use Dual Sentinels?
1. **True $\mathcal{O}(1)$ End Operations**: Both `PushFront`/`PopFront` and `PushBack`/`PopBack` run in constant time without special checks for empty lists.
2. **Symmetric Invariants**: Inserting or removing any node—whether first, middle, or last—uses identical, branchless pointer wiring:
   ```c
   node->prev->next = node->next;
   node->next->prev = node->prev;
   ```
3. **Guaranteed Non-NULL Neighbours**: Every valid payload node is always guaranteed to have a non-NULL `prev` and `next`.

---

## Features

- **Bidirectional Capabilities**: Full traversal and buffer export in both forward and reverse directions.
- **$\mathcal{O}(1)$ Operations**: Fast front and back insertion and deletion (`PushFront`, `PushBack`, `PopFront`, `PopBack`).
- **In-Place Reversal**: $O(n)$ time, $O(1)$ space reversal via pointer swap.
- **Robust Memory Management**: Complete leak-free teardown via `DList_Destroy(&list)` freeing all nodes and both sentinels.
- **Bidirectional Invariant Testing**: 43 automated unit test assertions verifying that `curr->next->prev == curr` and `curr->prev->next == curr` at all times.
- **Cross-Platform CI**: Automated builds and test validation with GCC, Clang AddressSanitizer, and Valgrind.

---

## Complexity Analysis

| Operation | Time Complexity (Average) | Time Complexity (Worst) | Space Complexity |
| :--- | :---: | :---: | :---: |
| `DList_PushFront` / `DList_PushBack` | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ |
| `DList_PopFront` / `DList_PopBack` | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ |
| `DList_InsertAfter` / `DList_InsertBefore` | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ |
| `DList_DeleteNode` | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ |
| `DList_GetFront` / `DList_GetBack` | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ |
| `DList_Find` | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ |
| `DList_GetAt` (with midpoint optimization) | $\mathcal{O}(n/2)$ | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ |
| `DList_Reverse` (in-place) | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ |
| `DList_Destroy` | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ |

---

## Project Structure

```text
DoublyLinkedList/
├── include/
│   └── doubly_linked_list.h     # Public API, types, and legacy compatibility
├── src/
│   └── doubly_linked_list.c     # Implementation
├── examples/
│   └── demo.c                   # Terminal showcase with forward/backward views
├── tests/
│   └── test_doubly_list.c       # Automated unit test suite (43 assertions)
├── .github/
│   └── workflows/
│       └── ci.yml               # GitHub Actions CI matrix
├── Makefile                     # Cross-platform build script
├── LICENSE                      # MIT License
├── .gitignore                   # Ignore binaries and temporary files
└── README.md                    # Project documentation
```

---

## Quick Start

### 1. Clone the Repository
```bash
git clone https://github.com/i7modes/DoublyLinkedList.git
cd DoublyLinkedList
```

### 2. Build and Run Demo
```bash
make demo
make run-demo
```

### 3. Run Automated Unit Tests
```bash
make check
```

Expected output:
```text
========================================
  Doubly Linked List Automated Tests
========================================

--- Test: Initialization & Sentinels ---
  [PASS] DList_Create returns non-NULL
  [PASS] New list is empty
  [PASS] New list size is 0
  [PASS] Empty list passes bidirectional integrity
...
========================================
  Results: 43/43 assertions passed
========================================
```

### 4. Run Memory Leak Check (Linux / WSL)
```bash
make test
valgrind --leak-check=full --show-leak-kinds=all ./bin/test_runner
```

---

## Code Example

```c
#include "doubly_linked_list.h"
#include <stdio.h>

int main(void) {
    // 1. Create list with head and tail sentinels
    DoublyList *list = DList_Create();

    // 2. O(1) Push operations at both ends
    DList_PushFront(10, list);
    DList_PushBack(20, list);
    DList_PushBack(30, list);

    // 3. Bidirectional traversals
    printf("Forward:  ");
    DList_PrintForward(list);  // [Head] <-> [10] <-> [20] <-> [30] <-> [Tail]

    printf("Backward: ");
    DList_PrintBackward(list); // [Tail] <-> [30] <-> [20] <-> [10] <-> [Head]

    // 4. In-place reversal
    DList_Reverse(list);
    DList_PrintForward(list);  // [Head] <-> [30] <-> [20] <-> [10] <-> [Tail]

    // 5. Clean up all memory
    DList_Destroy(&list);      // list is now NULL, 0 memory leaks!
    return 0;
}
```

---

## License

Distributed under the [MIT License](file:///c:/Users/i7mod/OneDrive/GitHub/DoublyLinkedList/LICENSE). Created by [i7modes](https://github.com/i7modes).
