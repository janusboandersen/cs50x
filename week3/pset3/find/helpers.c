/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"


/**
 * Recursive search function: Implements the binary search algorithm. Returns true if value is in array of n values, else false.
 */
bool bin_search(int key, int array[], int dimension, int start_index, int end_index)
{
    //requires a sorted array to be passed in! We could call sort here to be sure!
    
    //performs search from start_index to end_index
    
    //helper variables
    int middle_index;
    
    //while there is still something to search
    while ( (end_index - start_index) >= 0 )
    {
        //pick the middle-most position
        //if e-s = 0 then there is 1 element to look at. Set m = s (= e).
        //if e-s = 1 then there are 2 elements to look at. Just look at the first one. Set m = s.
        //if e-s > 1 then there are more than 2 elements to look at. Choose a middlemost index between s and e
        //  by truncated integer division: m = s+(e-s)/2 = (s+e)/2
        middle_index = (end_index - start_index) > 1 ? (end_index + start_index)/2 : start_index;
        
        //check the middle position for the key
        if (array[middle_index] == key)
        {
            //found it
            return true;
        }
        else if (array[middle_index] > key)
        {
            //recursively search the 'left' side of the array
            return bin_search(key, array, dimension, start_index, middle_index - 1);
        }
        else
        {
            //recursively search the 'right' side of the array
            return bin_search(key, array, dimension, middle_index + 1, end_index);
        }
        
    
    }
    
    //We didn't find it!
    return false;
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
 
    //call the recursive binary search function across the entire array
    return bin_search(value, values, n, 0, n-1);
 
 /* No more linear search! -- Everything below this line is linear search implementation --
 
    // Linear search algorithm
    for (int i = 0; i < n; i++)
    {
        if (values[i] == value)
            return true;
    }
    
    // The linear search did not yield a result
    return false;
    
    */
    
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Insert sort O(n^2), Ω(n)
    int element, j;
    
    //start the loop at 1, no sense to look at the first element alone - it's sorted
    for (int i = 1; i < (n - 1); i++)
    {
        
        //pick up the i-th element to figure out where it needs to go, and potentially slide sorted elements into its place
        element = values[i]; 
        
        j = i;  //the i counter indicates the first currently unsorted element. We need to work backwards from that to figure out where the element needs to go
        
        while (element < values[j-1] && j > 0) 
        {
            values[j] = values[j-1]; //slide the sorted values one place to the right
            j--; //decrement j for next loop or for placing the element
        }
        values[j] = element; //insert the element into the empty slot
        
    }
    
    //the by-ref modified array is the actual return - so here void.
    return;
}