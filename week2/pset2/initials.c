#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{

    //Get user's name as a string
    //printf("Please enter your username: ");
    string username = GetString();
    
    //Find some way to partition to initials
    //Cannot assume that users have capitalized their name(s)
    //Loop through looking for spaces
    //If the space is the last character, then don't use the following char

//    string initials;
//    initials = username;
//    initials = initials & initials;
    char tmp;    

    //Print result to stdout
    for (int i = 0, n = strlen(username) - 1; i < n; i++)
    {

        if (i == 0)
        {
            tmp = toupper(username[i]);
            printf("%c", tmp);
        }
        else if (username[i] == ' ')
        {
            tmp = toupper(username[i + 1]);
            printf("%c", tmp);
        }
            
    }
    
    printf("\n");

    return 0;

}