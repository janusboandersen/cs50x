#include <stdio.h>
#include <cs50.h>
#include <math.h>

/* This program implements a greedy algorithm
* in order to solve an optimization problem:
* minimum number of coins to exchange a given amount 
* (floating point number) into a set of US coins */


int main(void)
{
    //initialize the available coinset vector - 4 coins {quarter, dime, nickel, penny}
    int coin_denoms = 4;
    int coinset[4] = {25, 10, 5, 1};  //measured in cents, implemented in int for precision, divide by 100 to get dollars
    
    //declare the returnset vector (whole number of coins returned) of denomination corresponding to the coinset
    int returnset[4] = {0, 0, 0, 0};
    
    //prompt user for amount to be exchanged, and to track how much still remains to be exchanged
    double tmp_exchange_total;
    do
    {
        printf("Please enter amount to be exchanged to coins: ");
        tmp_exchange_total = GetFloat(); //leveraging CS50 functionality
    }
    while (tmp_exchange_total < 0);
    
    //int implementation for improved precision. Cast the float provided by the user into ints measured in cents.
    int exchange_total, exchange_remaining;
    tmp_exchange_total = roundf(tmp_exchange_total * 100);  //Scaling to cents and rounding to fix nasty imprecision issues
    exchange_total = (int) (tmp_exchange_total); //casting to int and conversion
    //printf("%f\n", tmp_exchange_total);
    exchange_remaining = exchange_total; //start condition for optimization
    
    //count number of coins
    int coin_count = 0;
    
    //If the coinset was not already sorted from high-to-low, here would be the place to do it!
    
    //Iteratively break down the exchange amount using integer division, and keep track of remaining to be exchanged, and number of coins used
    for (int i = 0; i < coin_denoms; i++)  //apparently no clever way of getting number of elements in an array ( sizeof(arr)/sizeof(arr[0]) is not a universally good way)
    {
        //find highest positive integer division of current coin into the remaining exchange amount - fortunately
        //we've ruled out negative amounts, and C automatically truncates during integer division
        returnset[i] = exchange_remaining / coinset[i];  //update vector
        exchange_remaining -= coinset[i]*returnset[i]; //update remaining amount and loop again
    
        coin_count += returnset[i];
    
        //Output for debugging
        //printf("%.2f x %2d = %.2f rem %3d cents out of total %d cents\n", (float) coinset[i]/100.0, returnset[i], (float) (coinset[i] * returnset[i] / 100.0), exchange_remaining, exchange_total);
    
    }
    
    //perform a check that everything went well
    int checksum = 0;
    for (int i = 0; i < coin_denoms; i++)
    {
        checksum += coinset[i] * returnset[i];
    }
    
    if (checksum != exchange_total)
        printf("Something went wrong in the divisions!\n");
    
    //output number of coins
    //printf("Total coins required: %d\n", coin_count);
    
    //Output compliant wis CS50 checker
    printf("%d\n", coin_count);
    
}