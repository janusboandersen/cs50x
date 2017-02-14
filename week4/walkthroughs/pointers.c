#include <stdio.h>
#include <string.h>

int main(void)
{
    char* s = "Janus\0";   //or GetString()
    
    if (s == NULL)
        return 1;
        
    for (int i = 0, n = strlen(s); i < 5*n; i++)
    {
        printf("%c", s[i % n]);
        //printf("%c\n", *(s+i));  //dereference operator on the i-th character of the string
    }

}