/**
 * helpers.h
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

/**
 * Recursive search function: Implements the binary search algorithm. Returns true if value is in array of n values, else false.
 */
bool bin_search(int key, int array[], int dimension, int start_index, int end_index);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n);

/**
 * Sorts array of n values.
 */
void sort(int values[], int n);