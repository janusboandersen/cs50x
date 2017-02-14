#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, char* argv[])
{
    //check for command line arguments - return 1 if more than 1 arg provided
    if (argc != 2) {
        printf("Error. Expected use: ./caesar.c 13 where 13 can be any number representing a rotation in the Caesar cipher algo.\n");
        return 1;
    }
    
    //proceed with the Caesar algorithm

    //Read the integer and write into the key variable
    int key = 0;
    sscanf(argv[1], "%d", &key);
    
    //Prompt user for a string to convert
    //printf("Please type plain text to be encrypted with the Caesar algorithm: \n");
    string plain_text = GetString();
    string cipher_text = plain_text;
    int ascii_offset = 65;
    int alphabet = 26;
    
    //Perform the rotation
    /* Rules:
    *  - Preserve uppercase-ing
    *  - Preserve lowercase-ing
    *  - Preserve non-letter chars?
    */
    
    //Loop through each character
    for (int i = 0, n = strlen(plain_text); i < n; i++)
    {
        //Rotate letters only inside two ranges: ASCII 65-90 and ASCII 97-122
        
        if (cipher_text[i] >= 'A' && cipher_text[i] <= 'Z') 
        {
            ascii_offset = 'A';
            cipher_text[i] = (cipher_text[i] - ascii_offset + key) % alphabet + ascii_offset;
            
        }
            
        else if (cipher_text[i] >= 'a' && cipher_text[i] <= 'z') 
        {
            ascii_offset = 'a';
            cipher_text[i] = (cipher_text[i] - ascii_offset + key) % alphabet + ascii_offset;
        }
        
    }
    
    //printf("Rotation with key = %d:\n", key);
    printf("%s\n", cipher_text);
    
    return 0;
    
}