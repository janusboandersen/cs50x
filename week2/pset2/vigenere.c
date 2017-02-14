#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
    //check for command line arguments - return 1 if more than 1 arg provided, if keyword contains non-alphabetical characters
    if (argc != 2) 
    {
        printf("Error. Expected use: ./vigenere.c keyword where 'keyword' can be any word without spaces representing a variable rotation.\n");
        return 1;
    } 


    //analyse the string for non-alphabetical characters.
    string key = argv[1];
    int key_len = strlen(key);
    
    char c;
    for (int i = 0; i < key_len; i++)
    {
         c = key[i];
         if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
         {
            printf("Non-alphabetical character found!\n");
            return 1;
         }
    }
        
    
    //proceed with the Vigenere / Variable-Caesar algorithm

    //Prompt user for a string to convert
    //printf("Please type plain text to be encrypted with the Caesar algorithm: \n");
    string plain_text = GetString();
    string cipher_text = plain_text;
    
    int upper_ascii_offset = 'A';
    int lower_ascii_offset = 'a';
    int alphabet = 26;
    
    int key_offset = 0;

    //Normalize the key to a range 0-25
    for (int i = 0; i < key_len; i++)
    {
        key[i] = toupper(key[i]);
        key[i] -= upper_ascii_offset;
    }
    
    //Perform the variable rotation
    /* Rules:
    *  - Preserve uppercase-ing
    *  - Preserve lowercase-ing
    *  - Preserve non-letter chars
    *  - Only go to next key letter if a character has been rotated
    */
    
    
    //Loop through each character to convert as needed, without touching the plaintext
    for (int i = 0, n = strlen(plain_text); i < n; i++)
    {
        //Rotate letters only - i.e. character inside one of the two ranges: ASCII 65-90 and ASCII 97-122
        
        if (cipher_text[i] >= 'A' && cipher_text[i] <= 'Z')
        {
            cipher_text[i] = ((cipher_text[i] - upper_ascii_offset) + key[key_offset]) % alphabet + upper_ascii_offset;
            key_offset = (key_offset + 1 == key_len) ? 0 : key_offset + 1;
        }
            
        else if (cipher_text[i] >= 'a' && cipher_text[i] <= 'z') 
        {
            cipher_text[i] = ((cipher_text[i] - lower_ascii_offset) + key[key_offset]) % alphabet + lower_ascii_offset;
            key_offset = (key_offset + 1 == key_len) ? 0 : key_offset + 1;
        }
        
    }
    
    //printf("Rotation with key = %d:\n", key);
    printf("%s\n", cipher_text);
    
    return 0;
}