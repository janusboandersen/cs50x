#include <cs50.h>
#include <stdio.h>

/* This program generates Mario half-pyramid shapes! */

int main(void)
{

    int pyramid_height;
    bool valid_input = false;

    //prompt user for pyramid height: we will accept non-negative integers from 1 to and including 23    
    do
    {
        printf("Pyramid height: Please input an integer between 1 and 23 (both included): ");
        pyramid_height = GetInt();
        
        //If the integer is zero end the program
        if (pyramid_height == 0)
            break;
        
        //Validate the input
        valid_input = (pyramid_height >= 1 && pyramid_height <= 23) ? true : false;
    }
    while (valid_input == false);
    
    
    //calculate the pyramid
    //pyramid_width is always pyramid_height + 1, so length of string to hold all 
    int pyramid_width = pyramid_height + 1;
    
    //Create a string for pyramid line-by-line, size of width+1 in order to hold \n. Padding with spaces ' ' or pound-signs
    //char pyramid_line_chars[pyramid_width + 100];

    //print a guide
    //printf("i is --  0---4---8---12--16--20--24\n");
    
    //loop through the needed lines, will loop between 1 and 23 times
    for (int i = 0; i < pyramid_height; i++)
    {
        
        //loop through the chars from left to right
        for (int j = 0; j < pyramid_width; j++)
        {
            //input either hashes or hashes - using the ternary operator - hashes only if eligible column
            //pyramid_line_chars[j] = (j > (pyramid_width - i - 3)) ? '#' : ' ';  
            if (j > (pyramid_width - (i + 2) - 1))  //deduct (i + 2) for two tiles in the top row and one more in each consecutive row, and deduct 1 more for index correction (base 0)
                printf("#");
            else
                printf(" ");
            
        }

        //put a line break in the last char
        //pyramid_line_chars[pyramid_width] = '\n';
        
        //Output the linebreak, and repeat
        printf("\n");
    }
}