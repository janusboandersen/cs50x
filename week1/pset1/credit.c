#include <cs50.h>
#include <stdio.h>
#include <string.h>

/*
* Check credit card number validity defined by algorithm of Hans Peter Luhn 

* Implementation considerations:
* - We don't know how many  a number the user will enter (uncertain bounds): Assume the maximum will be 16 as per the longest of Amex (15), MasterCard (16) and Visa (13 / 16)
* - We need a relatively efficient way to go through individual digits of a number:
*   - Idea: Treat the whole number as a string. Going back and forth through the ASCII table? Casting an int to a string and back?
*   - Perhaps there is a better decomposition mechanism using mod?
* - 
*/

//Helper functions prototyping - implementation at the bottom

//Function to count the number of digits in a number
int count_digits(long long n);

//Function to do digit-addition (adding individual digits of a number)
int add_digits(long long n);

//Function to decompose an integer into an array of individual digits by passing it the integer and an empty array (apparently, C cannot return an array!)
int decompose_digits(long long n, int * digits);

//Function to identify a card issuer based on the first two digits in the card number
string issuer_name(int two_digits);

int main(void)
{
    //Get a credit card number candidate for checking - up to 15 digits (theoretically 999 trillion+, int caps at 4 billion)
    long long credit_candidate;
    int credit_digits;

    //Prompt user - and outright reject anything that doesn't have at least 13 digits
    do
    {
        printf("Please enter a 13-, 15- or 16-digit potential credit card number: ");
        credit_candidate = GetLongLong();
        
        //count the digits
        credit_digits = count_digits(credit_candidate);
        //printf("%d digits entered.\n", credit_digits);
    }
    while (credit_digits < 1);
    
    
    //Decompose credit card number
    //Declare array to hold the decomposed integer digits
    int digit_decomposition[credit_digits];
    int tmp;
    tmp = decompose_digits(credit_candidate, &digit_decomposition[0]);  //pass the pointer to the array
    
    //We can already now determine based on the digits-vector what company has potentially issued the card - or it is clearly invalid.
    string issuer;
    issuer = issuer_name(digit_decomposition[0]*10+digit_decomposition[1]);
    
    //Wrong number of digits in the card number, or not having first two digits matching any issuer - INVALID, abort.
    if ( !(credit_digits == 13 || credit_digits == 15 || credit_digits == 16) ) // || strcmp(issuer, "INVALID"))
    {
        //halt the program
        printf("%s", "INVALID\n");
        return 0;    
    }
    
    //Otherwise, we have an issuer name, the card has an accepted number of digits, and we can continue to check the card number.
    //There wasn't any obvious reason to disqualify the card number. Now go through the steps in Hans Peter Luhn's algorithm
    
    //Rule 1. 2x of every other digit starting from the second last
    // If there is an even number of digits in the card number (case: 16   ), we can do it forward by taking digits 0, 2, 4, ... (zero-indexed array)
    // If there is an odd  number of digits in the card number (case: 13/15), we can do it forward by taking digits 1, 3, 5, ... (zero-indexed array)
    // We can control what index is taken by using a dummy-variable with value from {0,1}
    int dummy;
    if (credit_digits % 2 == 0) //even number
        dummy = 0;
    else                        //odd number
        dummy = 1;
        
    for (int i = (0 + dummy); i < credit_digits; i+=2) //increment by 2
    {
        digit_decomposition[i] = add_digits(2 * digit_decomposition[i]); //multiply number by itself and add together digits
        //printf("%2d : %4d\n", i, digit_decomposition[i]);
    }
    
    //Rule 2. Summarize the vector 
    int checksum = 0;
    for (int i = 0; i < credit_digits; i++)
    {
        checksum += digit_decomposition[i]; //sum across vector
        //printf("%2d : %4d\n", i, digit_decomposition[i]);
    }
    
    //Rule 3. The modulo of the summarized vector must be 0. I.e., last digit is zero.
    if (checksum % 10 != 0)
        printf("INVALID\n");
    else
    {
        //the card is valid - determine the type of card
        printf("%s\n", issuer);
    }
    

    return 0;
}

//Implementation of helper functions

//Function to count the number of digits in a number
//This function works by successive integer division by 10, and counts how many times it is possible to divide n by 10 before reaching 0. n = 0 is defined as having one digit.
int count_digits(long long n)
{
    int count = 0;
    
    do
    {
        n /= 10;
        count++;
    }
    while (n > 0);
    
    //printf("Count: %i\n", count);
    
    return count;
}


//Function to do digit-addition (adding individual digits of a number)
int add_digits(long long n)
{
    int sum_digits = 0;
    
    //count the number of digits.
    int count = count_digits(n);
    
    // if digits == 1 then sum is the digit itself - the trivial case
    if (count == 1)
    {
        sum_digits = n;
    }
    // if digits > 1 do decomposition into an array and run summation across array
    else if (count > 1)
    {
        //decompose
        int digs[count], tmp;
        tmp = decompose_digits(n, &digs[0]);
        
        //summation across vector
        for (int i = 0; i < count; i++)
        {
            sum_digits += digs[i];
        }
        
    }

    // return the sum
    return sum_digits;    
}

//Function to decompose an integer into an array of individual digits by passing it the integer and an empty array (apparently, C cannot return an array!)
int decompose_digits(long long n, int * digits)
{
    //the method here is to decompose a number, digit-by-digit by successive calls to get remainder of division by 10, r = (n mod 10).
    //the decomposition starts from the back, so the loop either should run from right-to-left, stacking up the return-array from index high-to-low,
    // or alternatively reversing the array after the decomposition run. The former approach has been chosen here.
    for (int i = count_digits(n) - 1; i >= 0; i--)
    {
        digits[i] = n % 10;
        n /= 10; // integer-division of n by 10, so any decimals are truncated 
    }
    while (n > 0);
    
    return 0; //return code 0 for successful run
}

string issuer_name(int two_digits)
{
    string issuer;
    
    switch (two_digits)
    {
        case 34:
        case 37:
            issuer = "AMEX";
            break;
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
            issuer = "VISA";
            break;
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
            issuer = "MASTERCARD";
            break;
        default:
            issuer = "INVALID";
            break;
    }
    return issuer;
}