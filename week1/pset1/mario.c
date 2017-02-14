#include <cs50.h>
#include <stdio.h>

/* This program generates Mario half-pyramid shapes! */

int main(void)
{

    int pyramid_height;

    //prompt user for pyramid height: we will accept non-negative integers from 0 to and including 23. 0 terminates program. 1-23 creates a pyramid.
    do
    {
        printf("Pyramid height: Please input an integer between 1 and 23 (both included): ");
        pyramid_height = GetInt();
        
        //If the integer is zero end the program
        if (pyramid_height == 0)
            break;
    }
    while (pyramid_height < 1 || pyramid_height > 23);
    
    //calculate the pyramid width: pyramid_width is always pyramid_height + 1
    int pyramid_width = pyramid_height + 1;
    
    //Create a string for pyramid line-by-line, size of width + 1 in order to also hold string terminator \0. 
    char pyramid_line_chars[pyramid_width + 1];

    //debugging print a guide for counting
    //printf("i is --  0---4---8---12--16--20--24\n");
    
    //loop through the needed lines, will loop between 1 and 23 times
    for (int i = 0; i < pyramid_height; i++)
    {
        
        //loop through the chars from left to right
        for (int j = 0; j < pyramid_width; j++)
        {
            //input either hashes or hashes - using the ternary operator - hashes only if eligible column
            //in the logic expression, we deduct (i + 2) for starting with two tiles in the top row and one more for each consecutive row, and deduct 1 more for index correction (base 0)
            pyramid_line_chars[j] = (j > (pyramid_width - (i + 2) - 1)) ? '#' : ' ';
        }

        //put a string terminator in the last char
        pyramid_line_chars[pyramid_width] = '\0';
        
        //Output the string, linebreak, and repeat
        printf("%s\n", pyramid_line_chars);
    }
}