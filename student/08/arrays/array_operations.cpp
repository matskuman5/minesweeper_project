#include "array_operations.hh"
#include <iostream>

/*
 * Returns the greatest element of the array.
 * int* itemptr: pointer to the first array element to be examined
 * int size: number of elements to be examined
 * return value: the greatest element of the array
 */
int greatest_v1(int *itemptr, int size)
{

    int greatest_element = 0;

    for(int* position = itemptr; position < itemptr + size; ++position){
        if (greatest_element < *position) {
            greatest_element = *position;
        }
    }

    return greatest_element;
}

/*
 * Returns the greatest element of the array.
 * int* itemptr: pointer to the first array element to be examined
 * int* endptr: pointer to the memory address after the last element of the array
 * return value: the greatest element of the array
 */
int greatest_v2(int *itemptr, int *endptr)
{

    int greatest_element = 0;

    for(int* position = itemptr; position < endptr; ++position){
        if (greatest_element < *position) {
            greatest_element = *position;
        }
    }

    return greatest_element;

}

/* Copies the content of the array to another array
 * int* itemptr: pointer to the first array element to be copied
 * int* endptr: pointer to the memory address after the last element of the array to be copied
 * int* targetptr: pointer to the head of the array, to which to copy
 */
void copy(int *itemptr, int *endptr, int *targetptr)
{
    for(int* position = itemptr; position < endptr; ++position) {
        *targetptr = *position;
        ++targetptr;
    }

}

/* Reverses the elements of the array
 * int* leftptr: pointer to the first element of the reversable part
 * int* rightptr: pointer to the next memory address after the reversable part
 */
void reverse(int *leftptr, int *rightptr)
{
    --rightptr;
    for(int* position = leftptr; position < rightptr; ++position) {
        int temp = *rightptr;
        *rightptr = *position;
        *position = temp;
        --rightptr;
    }

}
