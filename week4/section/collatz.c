#include <stdio.h>

int collatz(int n)
{
    
    //printf("Collatz(%i)->\n", n);
    
    //Base case
    if (n == 1)
        return 0;
    
    //Recursive case 1 for even numbers
    else if (n % 2 == 0)
        return 1 + collatz(n/2);

    //Recursive case 2 for odd numbers
    else
        return 1 + collatz(3 * n + 1);
}

int main(void)
{
    //collatz conjecture
    
    //Start value
    int seed = 5555;

    //Start the recursive algorithm
    int steps = collatz(seed);
    
    //Output the result
    printf("%i steps to reach 1.\n", steps);
    return 0;
}