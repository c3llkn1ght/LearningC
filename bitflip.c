#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int countBits(unsigned int x) {
    int count = 0;
    while (x) {
        // use bitwise AND to count least significant bit
        // left     right     AND
        //  0        0         0
        //  0        1         0
        //  1        0         0
        //  1        1         1
        // 1 = 00000001
        // AND-ing 1 will only step the count if the lowest bit of x is currently 1
        count+= x & 1;
        // shifting and asigning moves all the bits in x 1 place to the right
        // the lowest bit falls off
        // x = 13 --> 1101
        // x >>= 1 -> 0110
        // x = 6 ---> 0110
        x >>= 1;
    }
    //return how many bits were set
    return count;
}

int printBinary(unsigned int x, char *buffer) {
    // CHAR_BIT is the number of bits in a byte -- 8 bits in this case
    // sizeof(int) is 4 bytes
    // CHAR_BIT literaly evaluates to 8
    // sizeof(int) literaly evaluates to 4
    // 8 * 4 = 32 bits
    // so we have a 32 bit integer
    // because bit positions are zero indexed and we want the leftmost bit, we need to subtract 1
    // now we shift 1 - 00000000 00000000 00000000 00000001 - 31 bits to the left
    // our mask is  --> 10000000 00000000 00000000 00000000
    // why not just hardcode it?
    // unsigned int mask = 1 << 31
    // well, the size of an int is compiler-dependent
    // also, by the C standard, an int is only guaranteed to be at least 16 bits
    // so by doing it this way, the mask can be used on different architecture
    // for example, in x16 this mask would create a 16-bit integer with the 15th bit set
    unsigned int mask = 1 << ((sizeof(int))*CHAR_BIT-1);
    int i = 0;
    // okay cool, so we have our mask, but why'd we do that in the first place?
    // essentially we are going to slide it accross the length of x's bits, AND-ing each of them as we go
    // this will give us the raw bits of the integer x, from MSB to LSB, exactly the way the CPU stores it
    // we then have a ternary operator
    // condition ? true_value : false_value
    // if the bit was set, store 1, otherwise store 0
    while (mask) {
        buffer[i++] = (x & mask) ? '1':'0'; // store the bits in the appropriate array index
        mask >>= 1; // shift the bitmask 1 bit to the right
    }
    buffer[i] = '\0'; // null terminator at the end of the string
    printf ("binary: %s\n", buffer);
    return 0;
}

int readBinary(const char *buffer) {
    return (int) strtol(buffer, NULL, 2);
}

int bitflipAND(unsigned int x, char *buffer, int flip) {
    unsigned int mask = 1 << ((sizeof(int))*CHAR_BIT-1); // mask reused from earlier
    int i = 0;
    //we need to convert the flip varibale to LSB
    //using the logic here, if we used the position of flip as our stopping point, we would flip from MSB
    int flipLSB = sizeof(int)*CHAR_BIT - 1 - flip;
    // now we need a length of the same size as the string-to-be, minus the null terminator
    int length = sizeof(int) * CHAR_BIT;
    //finally, loop through the length of the string array
    for (int pos = 0; pos < length; pos++) {
        //at the position of our flip variable, reverse the ternary operation
        if (pos == flipLSB ) {
            buffer[i++] = (x & mask) ? '0':'1'; //reversed
        }
        else {
            buffer[i++] = (x & mask) ? '1':'0'; //normal
        }
        mask >>= 1;
    }
    buffer[i] = '\0'; //terminate the string
    //read the string as a string, then read it as a number
    printf ("AND bitflip\nnumber: %d\nbinary: %s\n", readBinary(buffer), buffer);
    //set x as the newly bitflipped number
    x = readBinary(buffer);
    //count the bits
    int result = countBits(x);
    printf("number of set bits: %d\n", result);
    return 0;
}

int bitflipXOR(unsigned int x, char *buffer, int flip) {
    //bitwise XOR x with a mask made by shifting an unsigned 1 left by "flip" bits
    x = x ^ (1U << flip);
    printf ("XOR bitflip\n");
    //print the resulting number
    printf("number: %d\n", x);
    //print the binary representation
    printBinary(x, buffer);
    //count the bits
    int result = countBits(x);
    printf("number of set bits: %d\n", result);
    return 0;
}

int main () {
    unsigned int x = 133742069;
    int flip = 0;
    char buffer[sizeof(int)*CHAR_BIT + 1]; // an array of 32 chars plus one extra to place the null terminator
    printf("number: %d\n", x);
    printBinary(x, buffer);
    int result = countBits(x);
    printf("number of set bits: %d\n", result);
    printf("\n");
    bitflipAND(x, buffer, flip);
    printf("\n");
    bitflipXOR(x, buffer, flip);
}