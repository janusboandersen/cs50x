#include <stdio.h>
#include <string.h>
#include <cs50.h>

int main(void)
{
    string s = GetString();
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')  //check if the letter is lowercase
        {
            printf("%c", s[i] - ('a' - 'A'));  //convert to uppercase
        }
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");

}