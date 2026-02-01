#include <stdio.h>
#include <stdlib.h>

//typedef creates an alias so we can type with the struct's name
typedef struct Resize{
    int *array; // pointer to where the numbers are
    int size; // how many numbers are there in this bitch
    int capacity; // how many numbers can we fit in this bitch
} Resize;

//function to create the array in memory
Resize *createArray(int capacity) {
    Resize *list = malloc(sizeof(Resize)); // allocate memeory for the struct itself
    list->size = 0; //start off with nothing in the array
    list->capacity = capacity; //we will pass a capacity in when creating the array
    list->array = malloc(sizeof(int) * capacity); //allocate memory for capacity integers
    return list;
};

//function to insert a new value into the array
void insertElement(Resize *list, int value) {
    //check if there's enough memory allocated to add a new element
    if (list->size >= list->capacity) {
        printf("list is full. More please (:\n");
        // if not, increase the capacity by double or 50%
        if (list->capacity <= 1) {
            list->capacity *= 2;
        }
        else {
            list->capacity += list->capacity / 2;
        }
        //allocate more memory for the resized array, but do it carefully
        int *tmp = realloc(list->array, sizeof(int) * list->capacity);
        if (!tmp){
            printf("oh no.\n");
            exit(1);
        }
        list->array = tmp;
    }
    //increase the size of the array and add the value now that we know we have space
    list->size++;
    list->array[list->size-1] = value;
    return;
}

void removeKey(Resize *list, int key) {
    //if the key is larger than the number of elements in the array, go fuck yourself
    if (key >= list->size || key < 0) {
        printf("bad keys. \n");
        return;
    }
    //shrink list size
    list->size--;
    //shift all the elements to the left of the key one over
    for (int i = key; i < list->size; i++) {
        list->array[i] = list->array[i+1];
    }

    //if the list capacity is greater than 2 but more than double the list size, shrink the capacity
    if (list->capacity > 2){
        if (list->size <= list->capacity / 2){
            list->capacity /= 2;
            int *tmp = realloc(list->array, sizeof(int) * list->capacity);
            if (!tmp) {
                printf("oh no.\n");
                exit(1);
            }
            list->array = tmp;
        }
    }
    return;
}

void printArray(Resize *list) {
    printf("capacity: %d\n", list->capacity);
    printf("size: %d\n", list->size);
    for (int i = 0; i < list->size; i++) {
        printf("%d\n", list->array[i]);
    }
}

int main () {
    int capacity = 2;
    Resize *list = createArray(capacity);
    insertElement(list, 10);
    printArray(list);
    insertElement(list, 20);
    printArray(list);
    insertElement(list, 30);
    printArray(list);
    insertElement(list, 40);
    printArray(list);
    insertElement(list, 50);
    printArray(list);
    insertElement(list, 60);
    insertElement(list, 70);
    insertElement(list, 80);
    insertElement(list, 90);
    printArray(list);
    removeKey(list, 2);
    removeKey(list, 7);
    removeKey(list, 0);
    removeKey(list, 1000);
    removeKey(list, 6);
    removeKey(list, 0);
    removeKey(list, 0);
    removeKey(list, 0);
    removeKey(list, 0);
    printArray(list);
    insertElement(list, 666);
    insertElement(list, 67);
    insertElement(list, 69);
    printArray(list);
    return 0;
}