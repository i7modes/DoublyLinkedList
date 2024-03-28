#include <stdio.h>
#include <stdlib.h>
struct node {

       int Data;
       struct node* Next;
       struct node* Previous;
};

struct node* MakeEmpty(struct node* head, struct node* tail);
void Insert(int, struct node*, struct node*, struct node*);
void PrintList(struct node*);
int IsLast(struct node*, struct node*);
void Delete(int, struct node*);
struct node* FindPrevious(int, struct node*);
struct node* Find(int, struct node*);
int IsEmpty(struct node*);
int size(struct node*);
void DeleteList(struct node*);


int main(){
    struct node* head = MakeEmpty(NULL, NULL);
    struct node* tail = head->Next;

    printf("%d\n", IsEmpty(head));

    Insert(10, head, tail, head);
    Insert(20, head, tail, head->Next);
    Insert(30, head, tail, head->Next->Next);
    Insert(40, head, tail, tail->Previous->Previous);
    PrintList(head);

    printf("%d\n", IsEmpty(head));

    printf("%d\n", size(head));

    printf("%d\n", IsLast(head->Next->Next->Next->Next, head));

    printf("%d\n", Find(30, head)->Data);

    printf("%d\n", FindPrevious(30, head)->Data);

    Delete(20, head);
    PrintList(head);

    printf("%d\n", size(head));

    struct node* List = MakeEmpty(head, tail);
    PrintList(List);

    printf("\n Done!\n");
    return 0;

}

struct node* MakeEmpty(struct node* head, struct node* tail) {
    // Delete the list if it's not empty
    if (head != NULL && tail != NULL)
        DeleteList(head);

     head = (struct node*)malloc(sizeof(struct node));
     tail = (struct node*)malloc(sizeof(struct node));

    if (head == NULL || tail == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    head->Next = tail;
    head->Previous = NULL;

    tail->Next = NULL;
    tail->Previous = head;

    return head;
}

/*struct node* MakeEmpty() {

    struct node* head = (struct node*)malloc(sizeof(struct node));
    struct node* tail = (struct node*)malloc(sizeof(struct node));

    if (head == NULL || tail == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    head->Next = tail;
    head->Previous = NULL;

    tail->Next = NULL;
    tail->Previous = head;

    return head;
}*/

void Insert(int X, struct node* head, struct node* tail, struct node* P) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));

    if (temp == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    temp->Data = X;
    temp->Next = P->Next;
    temp->Previous = P;

    if (P->Next != NULL) // If P is not the tail
        P->Next->Previous = temp;
    else
        tail->Previous = temp; // Update tail's previous to the new node

    P->Next = temp;
}

void PrintList(struct node* head) {
    struct node* P = head->Next;
    if(IsEmpty(head)){
      printf("Empty list\n");

    } else {
    while (P->Next != NULL) {
        printf("%d\t", P->Data);
        P = P->Next;
    }
    printf("\n");
  }
}

int IsEmpty(struct node* head) {
    return head->Next->Next == NULL;
}

struct node* Find(int X, struct node* head){
    struct node* current = head->Next;
    while (current != NULL && current->Data != X) {
        current = current->Next;
    }

    return current;
}


struct node* FindPrevious(int X, struct node* head){
    struct node* current = head->Next;

    while (current->Next != NULL && current->Data != X) {
        current = current->Next;
    }

    if (current->Next == NULL && current->Data != X) {
        printf("Node with value %d not found.\n", X);
        return NULL;
    }

    return current->Previous;
}

int IsLast(struct node* P, struct node* L) {
    return P->Next->Next == NULL;
}

void Delete(int X, struct node* L){
     struct node* P;
     struct node* temp;

     P = FindPrevious(X, L);


     if(!IsLast(P, L) ){
         temp = P->Next;
         P->Next = temp->Next;
         free(temp);
     }
}

void DeleteList(struct node* head) {
    struct node* current = head->Next; // Start from the first element after the head
    struct node* temp;

    while (current != NULL && current->Next != NULL) { // Exclude the tail node
        temp = current->Next; // Store the next node before freeing current
        free(current);
        current = temp; // Move to the next node
    }

    // After deleting all nodes except tail, reset head's next pointer
    head->Next = NULL;
}

int size(struct node* head) {
    struct node* current = head->Next; // Start from the first element after the head
    int count = 0;

    while (current != NULL && current->Next != NULL) {
        count += 1;
        current = current->Next;
    }

    return count;
}
