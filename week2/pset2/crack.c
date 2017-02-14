#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>

/*

andi:HALRCq0IBXEPM
caesar:50zPJlUFIYY0o
eli:50MxVjGD7EfY6
hdan:50z2Htq2DN2qs
jason:50CMVwEqJXRUY
john:50TGdEyijNDNY
levatich:50QykIulIPuKI
rob:50q.zrL5e0Sak
skroob:50Bpa7n/23iug
zamyla:HAYRs6vZAb4wo

andi:Berkeley
caesar:13
eli:yale
hdan:boola
jason:Silliman
john:harvard
levatich:PBJ
rob:password
skroob:12345
zamyla:password

*/

int main(int argc, char* argv[])
{
    //check for command line arguments - return 1 if more than 1 arg provided
    if (argc != 2) 
    {
        printf("Error. Expected use: ./crack hashed_password \n");
        return 1;
    }
    
    //The password to crack from the user
    char *hash_password = argv[1];
    
    //Guessing variables
    char guess[9];
    //char *guess;
    char *hash_guess; //= "HADpUNMFEE1Rs";
    
    //Get the salt from the hashed password
    char salt[3]; //To store 2 chars of Base64
    
    strncpy(salt, hash_password, 2);
    salt[2] = '\0';  //terminate the string

    
    //Perform a dictionary attack
    
    //Perform a brute-force attack

    //make a guess
    
    //try numbers
    for (int i = 0; i < 99999999; i++)
    {
    
        
        //convert to a string
        sprintf(guess, "%d", i);

        //run the guess through salting and hashing
        hash_guess = crypt(guess, salt);
        //puts(hash_guess);

        //check if the passwords are equal
        if (strncmp(hash_guess, hash_password, 13) == 0) //check for equality
        {
            puts(guess); //success
            return 0;
        }
        
        //No? Try again!
    }
}