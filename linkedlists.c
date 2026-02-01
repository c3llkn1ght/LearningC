#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node {
    struct Node *next;
    struct Node *prev;
    (void*) data;
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
        Node *newNode = (Node*) malloc(sizeof(Node)); //allocate struct memory
        newNode->next = NULL; //if theres nothing in the list, there's nothing to point to
        newNode->prev = NULL; //if theres nothing in the list, there's nothing to point to
        newNode->data = malloc(valueSize); //allocate memory based on the size of the data
        memcpy(newNode->data, value, valueSize); //copy the value into the allocated memory
        list->head = &newNode;  //set the list head as the pointer of the new node
        list->tail = &newNode; //set the list tail as the pointer value of the new node
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
        list->tail = &newNode; //set the list tail as the pointer value of the new node
        list->size++; //increase the size of the list
        return newNode;
    }
}

void removeNode(LinkedList *list, int key) {
    //if the key is too big or too small, go fuck yourself
    if (0 <= key && key < list->size) {
        printf("fuck your keys.\n");
        return;
    }
    //if theres only one node in the list, fuck your list
    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    }
    //take note of the first and last nodes
    current = list->head;
    last = list->tail;
    //if the key is the first item in the list, overwrite the list head with the pointer of the next node
    if (key == 0) {
        list->head = list->head->next;
    }
    //if the key is the last item in the list, overwrite the tail with the pointer of the node previous to it 
    if (key == list->size - 1) {
        list->tail = list->tail->prev;
    }
    //iterate through the nodes until we reach the key
    for (int i = 0; i <= key;  i++) {
        current = current->next;
        //when we get to the key, copy the next and previous pointers in the node to temporary variables
        if (i == key) {
            a = current->prev;
            b = current->next;
            //go back to the previous node and overwrite its next pointer
            current = current->prev;
            current->next = b;
            free(current->data); // free the memory
            //advance to the pointer we just wrote and overwrite its previous pointer
            current = current->next;
            current->prev = a;
        }
    }
    list->size--; //decrease the size of the list
    return;
}

int main () {
    LinkedList *list = createList();
    Node *newNode();
}