#include <stdio.h>
#include <stdlib.h>
struct node {

       int Data;
       struct node* Next;
       struct node* Previous;
};

struct node* MakeEmpty(struct node*);
int IsEmpty(struct node*);
int IsLast(struct node*, struct node*);
struct node* Find(int, struct node*);
struct node* FindPrevious(int, struct node*);
void Delete(int, struct node*);
void Insert(int, struct node*, struct node*, struct node*);
void InsertLast(int, struct node*);
void PrintList(struct node*);
void DeleteList(struct node*);
int size(struct node*);

int main(){
    struct node* MyList = MakeEmpty(NULL);
    struct node* tail = MyList->Next;

    printf("%d\n", IsEmpty(MyList));

    Insert(10, MyList, tail, MyList);
    Insert(20, MyList, tail, MyList->Next);
    Insert(30, MyList, tail, MyList->Next->Next);
    //Insert(40, MyList, tail, tail->Previous);
    InsertLast(40, MyList);
    PrintList(MyList);

    printf("%d\n", IsEmpty(MyList));

    printf("%d\n", size(MyList));

    printf("%d\n", IsLast(MyList->Next->Next->Next->Next, MyList));

    printf("%d\n", Find(30, MyList)->Data);

    printf("%d\n", FindPrevious(30, MyList)->Data);

    Delete(20, MyList);
    PrintList(MyList);

    printf("%d\n", size(MyList));

    struct node* List = MakeEmpty(MyList);
    PrintList(List);

    printf("\nDone!\n");
    return 0;

}

struct node* MakeEmpty(struct node* head) {
    struct node* tail;
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

int IsEmpty(struct node* L) {
    return L->Next->Next == NULL;
}

int IsLast(struct node* P, struct node* L) {
    return P->Next->Next == NULL;
}

struct node* Find(int X, struct node* L){
    struct node* P = L->Next;
    while (P != NULL && P->Data != X) {
        P = P->Next;
    }

    return P;
}

struct node* FindPrevious(int X, struct node* L){
    struct node* P = L->Next;

    while (P->Next != NULL && P->Data != X) {
        P = P->Next;
    }

    return P;
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

void Insert(int X, struct node* head, struct node* tail, struct node* P) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));

    if (temp == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    temp->Data = X;
    temp->Next = P->Next;
    temp->Previous = P;

    if (P->Next != NULL)
        P->Next->Previous = temp;
    else
        tail->Previous = temp; 

    P->Next = temp;
}

void InsertLast(int X, struct node* L) {
    struct node* temp;
    struct node* P = L;
    temp = (struct node*)malloc(sizeof(struct node));

    if (temp == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    temp->Data = X;

    while(P->Next != NULL){
        P = P->Next;
    }

    temp->Next = P;
    temp->Previous = P->Previous;
    P->Previous->Next = temp;
    P->Previous = temp;
}

void PrintList(struct node* L) {
    struct node* P = L->Next;
    if(IsEmpty(L)){
      printf("Empty list\n");

    } else {
    while (P->Next != NULL) {
        printf("%d\t", P->Data);
        P = P->Next;
    }
    printf("\n");
  }
}

void DeleteList(struct node* L) {
    struct node* P = L->Next;
    struct node* temp;

    while (P != NULL && P->Next != NULL) { 
        temp = P->Next; 
        free(P);
        P = temp; 
    }

    L->Next = NULL;
}

int size(struct node* L) {
    struct node* P = L->Next;
    int count = 0;

    while (P != NULL && P->Next != NULL) {
        count += 1;
        P = P->Next;
    }

    return count;
}
