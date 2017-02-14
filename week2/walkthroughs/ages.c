#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        printf("Number of people in the room?: ");
        n = GetInt();
    }
    while (n < 1);
    
    int ages[n];
    
    for (int i = 0; i < n; i++)
    {
        printf("Age of person #%i: ", i + 1);
        ages[i] = GetInt();
    }
    
    printf("Time passes...\n");
    
    //Age by a year
    for (int i = 0; i < n; i++)
    {
        printf("A year from now person #%i will be %i years old.\n", i + 1, ages[i] + 1);
    }
    
}