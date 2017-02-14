#include <stdio.h>
#include <stdlib.h>

//Prototypes
int count_file_chars(char* filename);

int main(void)
{
    //some code here
}

int count_file_chars(char* filename)
{
    FILE* thefile;
    char ch;
    int count = 0;
    
    thefile = fopen("filename", r);
    if (thefile == NULL)
        return -1;  //report that an error has occured
    
    while ((ch = fgetc(thefile)) != EOF)
        count ++;
        
    
    fclose(thefile);
    
    return count;
        
}