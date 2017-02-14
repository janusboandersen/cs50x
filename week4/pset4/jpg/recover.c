/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdint.h>
#include <cs50.h>
#define MEMBUFFER 512  //For the FAT32 sector size


//Fixed-width 8-bit unsigned integer (system-independent) as primitive for a byte
typedef uint8_t BYTE;


//prototypes
bool isJPEG(BYTE buffer[], BYTE magic_number[]);


int main(int argc, char* argv[])
{
    //No command line arguments
    
    //Open the raw file for reading
    FILE* inptr = fopen("card.raw", "r"); 
    
    //validate that file is successfully opened
    if (inptr == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }
    
    
    //Data structure to hold the bytes read from the raw file
    BYTE buffer[MEMBUFFER];
    
    //Data structure for the first three bytes of the magic number, and the lower/upper limits of the fourth
    BYTE magic_number[5] = {0xFF, 0xD8, 0xFF, 0xE0, 0xEF};

    //control file in progress
    typedef struct
    {
        FILE* file_pointer;
        char file_name[8];
        int file_id;
    } jpeg_file;
    
    //declare and initialize a JPEG file datastructure to work with
    jpeg_file current_jpeg;
    current_jpeg.file_pointer = NULL;  //We use this to check if there is a file open currently
    current_jpeg.file_id = 0;  //Initializes the sequence of IDs 000...049 or however many JPEGs there are.
    
    
    //Scanning through the file in 512B chunks
    while (fread(&buffer, MEMBUFFER, 1, inptr) > 0)  //continue as long as chunks are being read
    {
        
        //Encountered a new JPEG signature and there is currently a file open -> Close file to prepare for a new file
        if (isJPEG(buffer, magic_number) && current_jpeg.file_pointer != NULL) 
        {
            //Close the current file - it's done
            fclose(current_jpeg.file_pointer);
            current_jpeg.file_pointer = NULL;
            
            //increment the id counter for next file
            current_jpeg.file_id += 1;
        }
        
        //Did not encounter a JPEG signature, but there is currently a file open -> Keep writing to that file
        else if (current_jpeg.file_pointer != NULL)
        {
            //Write the current chunk to the file
            fwrite(&buffer, MEMBUFFER, 1, current_jpeg.file_pointer);            
        }
        
        //Encountered a JPEG signature and there is no file open -> Open new file
        if (isJPEG(buffer, magic_number) && current_jpeg.file_pointer == NULL)  
        {
            //name the new JPEG file
            sprintf(current_jpeg.file_name, "%03d.jpg", current_jpeg.file_id);
            
            //Attempt to Open a new file with write access: Format name like 001.jpg
            //Simultaneously sets the pointer so we can track file openness
            current_jpeg.file_pointer = fopen(current_jpeg.file_name, "w");
            
            if (current_jpeg.file_pointer == NULL)  //The pointer should not be NULL here
            {
                printf("Error attempting to open file %s.\n", current_jpeg.file_name);
                return 1; 
            }
            
            //SUCCESS in opening the new file
            
            //Write the current chunk to the file
            fwrite(&buffer, MEMBUFFER, 1, current_jpeg.file_pointer);
            
        }
        
    }
    
    //Close the raw file, close the last JPEG file and end the program
    fclose(inptr);
    fclose(current_jpeg.file_pointer);
    return 0;
    
}

//This function checks the signature of the first 4 bytes to determine if it matches as JPEG
bool isJPEG(BYTE buffer[], BYTE magic_number[])
{
    //check for the JPEG magic number signature in the file
    if (buffer[0] == magic_number[0] && buffer[1] == magic_number[1] && buffer[2] == magic_number[2] && (buffer[3] >= magic_number[3] && buffer[3] <= magic_number[4]))
    {
        return true;
    }
    return false;
}
