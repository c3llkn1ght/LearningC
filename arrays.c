#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // make an array, then iterate through it using array syntax
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    for (int i = 0; i <= 19; i++) {
        printf("%d\n", array[i]);
    }

    // in C, the name of an array is actually a pointer to the first element
    printf("%p\n", (void*)array);

    //iterate through the memory addresses of array elements, the first element's address is what we just printed
    for (int j = 0; j <= 19; j++) {
        printf("%p\n", (void*)&array[j]);
    }

    //create an unititialized array of a fixed size
    int array1[20];

    int* p = array; //p is an 8-byte variable whose bits are interpreted as a memory address
    //a pointer is always 8 bytes (64 bits) in x64
    //the CPU goes to the address and reads a 4 byte value, the length of an integer in x64
    //basically saying “When I dereference p, treat 4 bytes found at that address as an int"
    //the pointer is 8 bytes (the address), and the integer it points to is 4 bytes (the value in the address)

    int x = 0; // integer value
    printf("x = %d\n", x);
    printf("the address in variable p: %p\n", p);
    //You turn a pointer into a value with *:

    printf("integer at address p: %d\n", *p);
    int x2 = *p; // x2 is assigned as the integer value that pointer p is pointing to
    printf("x2 = %d, the integer p points to\n", x2);

    //You turn a value into a pointer with &:

    p = &x; // p will point to x using it's address
    printf("p = %d, the value stored at the memory address of x\n", *p);
    int* p2 = &x2;
    printf("p2 = %d, pointing to the memory address of x2\n", *p2);

    //iterate through the array using pointers instead of array syntax

    for (int k = 0; k <= 19; k++) {
        printf("%d\n", *(array + k));
    }

    //iterate through the heap

    int *p3 = malloc(20*sizeof(int)); //allocate enough memeory for 20 integers
    int *p4 = malloc(sizeof(int[20])); //the same but allocates enough memory for a 20 integer array on whatever arch
    int *p5 = malloc(4*sizeof *p5); //same but works if the type changes

    // in C an if statement checks if something is 0
    // if it fails to allocate memory the it will send back a 0 (null pointer)
    if (p5) {
        for (int l = 0; l <= 19; l++) {
            p5[l] = l + 1;
        }
        for (int m = 0; m <= 19; m++) {
            printf("%d\n", p5[m]);
        }
    }

    free(p3);
    free(p4);
    free(p5);

    return 0;
}

