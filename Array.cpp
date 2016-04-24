#include "Array.h"
#include <stdlib.h>
#include <iostream>
#include "Numerics.h"

void swap(int* array, int pos1, int pos2) {
    if (pos1 == pos2)
        return;
    
    int tmp = array[pos1];
    array[pos1] = array[pos2];
    array[pos2] = tmp;
}

void print(int *array, int count) {
    for (int i=0; i<count; i++) {
        std::cout << array[i] << std::endl;
    }
}

void fillWithRandomNumbers(int *array, int length, int minValue, int maxValue) {
    for (int i=0; i<length; i++) {
        array[i] = rand() % (maxValue - minValue) + minValue;
    }
}

void fillWithAscendingNumbers(int *array, int length) {
    for (int i=0; i<length; i++)
        array[i] = i;
}

int getPositionOfFirstNumberLargerThan(int *array, int count, int number) {
    for (int i=0; i<count; i++) {
        if (array[i] > number)
            return i;
    }
    
    return -1;
}

int linearSearch(int* array, int size, int search_value) {
    for (int i=0; i<size; i++)
        if (array[i] == search_value)
            return i;
    
    return -1;
}

int binarySearch(int *array, int size, int search_value) {
    if (size == 0)
        return -1;
    
    int midle_pos = size /2;
    int midle_value = array[midle_pos];

    if (midle_value == search_value)
        return midle_pos;
    else if (search_value < midle_value)
        return binarySearch(array, midle_pos, search_value);
    else
        return binarySearch(array+midle_pos+1, midle_pos, search_value);
}

bool selfOrganizingContains(int* array, int size, int search_value) {
    for (int i=0; i<size; i++)
        if (array[i] == search_value) {
            swap(array, 0, i);
            return 0;
        }
    
    return -1;
}

int fibonacci_numbers[20];

int fibonacciSearch(int *array, int length, int search_value) {
    if (fibonacci_numbers[19] != 6765)
        getFibonacciNumbers(fibonacci_numbers, 20);

    int index = getPositionOfFirstNumberLargerThan(fibonacci_numbers, 20, length);
    return fibonacciSearchRecursive(array, length, search_value, fibonacci_numbers, 0, index);
}

int fibonacciSearchRecursive(int *array, int length, int search_value, int *fibonacci_numbers, int offset, int fib_idx) {
    if (fib_idx == 0)
        return -1;

    int fib2 = fibonacci_numbers[fib_idx-2];
    
    if (array[offset + fib2] == search_value)
        return offset + fib2;
    else if (array[offset + fib2] < search_value)
        return fibonacciSearchRecursive(array, length, search_value, fibonacci_numbers, offset+fib2, fib_idx-1);
    else 
        return fibonacciSearchRecursive(array, length, search_value, fibonacci_numbers, offset, fib_idx-2);
}

bool isSorted(int *array, int length) {
    for (int i=1; i<length; i++) {
        if (array[i] < array[i-1]) {
            return false;
        }
    }
    
    return true;
}

int findMinimumPosition(int *array, int start, int end) {
    int minValue = array[start];
    int minPos = start;
    
    for (int i=start+1; i<end; i++) {
        if (array[i] < minValue) {
            minValue = array[i];
            minPos = i;
        }
    }
    
    return minPos;
}

void selectionSort(int *array, int length) {
    for (int i=0; i<length; i++) {
        int pos = findMinimumPosition(array, i, length);
        swap(array, i, pos);
    }
}

bool bubbleUp(int *array, int length) {
    bool did_swap = false;
    for (int i=1; i<length; i++) {
        if (array[i-1] > array[i]) {
            swap(array, i-1, i);
            did_swap = true;
        }
    }
    
    return did_swap;
}

void bubbleSort(int *array, int length) {
    for (int i=0; i<length; i++) {
        if (!bubbleUp(array, length-i))
            break;
    }
}