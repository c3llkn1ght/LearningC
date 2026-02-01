#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node {
    struct Node *next;
    struct Node *prev;
    void *data;
} Node;

typedef struct LinkedList {
    Node *head;
    Node *tail;
    int size;
} LinkedList;

LinkedList *createList() {
    LinkedList *list = malloc(sizeof(LinkedList)); // allocate struct memory
    list->head = NULL; // start with no head
    list->tail = NULL;  // start with no tail
    list->size = 0; // start with nothing in the list
    return list;
}

Node *newNode(LinkedList *list, void *value, size_t valueSize) {
    //fresh node for an empty list
    if (list->size == 0) {
        Node *newNode = malloc(sizeof(Node)); //allocate struct memory
        newNode->next = NULL; //if theres nothing in the list, there's nothing to point to
        newNode->prev = NULL; //if theres nothing in the list, there's nothing to point to
        newNode->data = malloc(valueSize); //allocate memory based on the size of the data
        memcpy(newNode->data, value, valueSize); //copy the value into the allocated memory
        list->head = newNode;  //set the list head as the pointer of the new node
        list->tail = newNode; //set the list tail as the pointer value of the new node
        list->size++; // increase the size of the list
        return newNode;
    }
    //there's already a list, we need to add out node to that list
    else {
        Node *newNode = (Node*) malloc(sizeof(Node)); // allocate struct memory
        newNode->next = NULL; // we're adding to the end of the list, this is now the last node
        newNode->prev = list->tail; //pointer to the node previous to this node
        newNode->data = malloc(valueSize); // allocate memory based on the size of the data
        memcpy(newNode->data, value, valueSize); //copy the value into the allocated memory
        list->tail->next = newNode;
        list->tail = newNode; //set the list tail as the pointer value of the new node
        list->size++; //increase the size of the list
        return newNode;
    }
}

void removeNode(LinkedList *list, int key) {
    //if the key is too big or too small, go fuck yourself
    if (key < 0 || key >= list->size) {
        printf("bad keys.\n");
        return;
    }
    //take note of the first node
    Node *current = list->head;

    //iterate through the nodes until we reach the key
    for (int i = 0; i < key;  i++) {
        current = current->next;
    }

    //create temporary node pointers for the current "next" and "prev" pointers
    Node *prev = current->prev;
    Node *next = current->next;

    if (prev) {
        prev->next = next; //if there is a previous node, overwrite the node
        //prev.next = &next
    }
    else {
        list->head = next; // if theres no previous node, we simply overwrite the head
        //list.head = &next
    }

    // the current node is now deindexed from the left side

    if (next) {
        next->prev = prev; //if there is a next node, overwrite the node
        //next.prev - &prev
    }
    else {
        list->tail = prev; // if theres no previous node, we simply overwrite the tail
        //list.tail = &prev
    }

    //the current node is now deindexed from the right side
    //the node is isolated, floating in memory

    free(current->data);// free the memory allocated for data
    free(current); // free the memory allocated for the struct
    list->size--; //decrease the size of the list

    return;
}

LinkedList *printList(LinkedList *list) {
    printf("size: %d\n", list->size);
    Node *current = list->head;
    for (int i = 0; i < list->size; i++) {
        printf("node %d: %d\n", i + 1, *(int*)current->data);
        current = current->next;
    }
    return 0;
}

int main () {
    LinkedList *list = createList();
    int *x = (int*) malloc(sizeof(int));
    *x = 1;
    int *y = (int*) malloc(sizeof(int));
    *y = 2;
    int *z = (int*) malloc(sizeof(int));
    *z = 3;
    int *a = (int*) malloc(sizeof(int));
    *a = 4;
    int *b = (int*) malloc(sizeof(int));
    *b = 5;
    int *c = (int*) malloc(sizeof(int));
    *c = 6;
    int *d = (int*) malloc(sizeof(int));
    *d = 7;
    int *e = (int*) malloc(sizeof(int));
    *e = 8;
    int *f = (int*) malloc(sizeof(int));
    *f = 9;
    int *g = (int*) malloc(sizeof(int));
    *g = 10;
    newNode(list, x, sizeof(int));
    newNode(list, y, sizeof(int));
    newNode(list, z, sizeof(int));
    newNode(list, a, sizeof(int));
    newNode(list, b, sizeof(int));
    newNode(list, c, sizeof(int));
    newNode(list, d, sizeof(int));
    newNode(list, e, sizeof(int));
    newNode(list, f, sizeof(int));
    newNode(list, g, sizeof(int));
    printList(list);
    removeNode(list, 0);
    printList(list);
    removeNode(list, 8);
    printList(list);
    removeNode(list, 3);
    printList(list);
    removeNode(list, 100);
    removeNode(list, -1);
}