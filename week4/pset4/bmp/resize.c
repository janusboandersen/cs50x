/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a BMP -  piece by piece
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    //TODO ensure proper usage - 4 args needed: 
    //1st: program
    //2nd: scaling factor (n= 1..100) to apply both vertically and horizontally.
    //3rd: infile
    //4th: outfile
    
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember scaling factor and filenames
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    //check the scaling factor
    if (n < 1 || n > 100)
    {
        printf("Usage: n expected to be between 1..100.\n");
        return 1;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }


    /* Resize/scaling image: 
     * Every pixel repeated n times, every row repeated n times
     * new_width = n x old_width
     * new_height = n x old_height
     *
     * Approach:
     * Horizontally write each pixel n times, and adjust padding
     * Vertically write each NEW horizontal line n times.
     *
     * Method 1: Re-write
     * Create or remember NEW pixels in an array, and write out array as many times as needed (vertically)
     * 
     * Method 2: Re-copy
     * Algorithmically process each scanline n-times; i.e., n-times loop over the same line being scaled and copied.
     * 
     */
    

    //Calculate new headers
    //TODO: 
    //Declare structs to hold
    BITMAPFILEHEADER bf2 = bf;
    BITMAPINFOHEADER bi2 = bi;


    
    // modify width: biWidth (width of image in pixels - does not include padding)
    bi2.biWidth *= n;
    
    // modify height: biHeight (height of image in pixels)
    bi2.biHeight *= n;

    // determine padding per scanline (in the old file)
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;  //why not just (bi2.biWidth * sizeof(RGBTRIPLE) % 4  ???

    // determine padding per scanline (based on new size, to be outputted to new file)
    int padding2 =  (4 - (bi2.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;  //why not just (bi2.biWidth * sizeof(RGBTRIPLE) % 4  ???

    // modify image size: biSizeImage (total size of image in bytes - includes pixels and padding) 
    bi2.biSizeImage = abs(bi2.biHeight) * (bi2.biWidth * (bi2.biBitCount / 8) + padding2);

    // modify file size: bfSize
    bf2.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi2.biSizeImage;


    // write outfile's BITMAPFILEHEADER
    fwrite(&bf2, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi2, sizeof(BITMAPINFOHEADER), 1, outptr);


    //TODO: Apply scaling factor through iteratively writing to file

    // temporary storage
    RGBTRIPLE triple;  //for a single pixel
    RGBTRIPLE triples_array[bi2.biWidth - 1];  //for all pixels in a scanline (not the padding)
    int pixel_pos_in_array = 0;  //to keep track of the position in the array

    // iterate over infile's scanlines
    for (int scanline = 0, biHeight = abs(bi.biHeight); scanline < biHeight; scanline++)
    {
        
        //reset the position in the array
        pixel_pos_in_array = 0;
        
        // iterate over pixels in scanline in original file
        for (int pixel = 0; pixel < bi.biWidth; pixel++)
        {
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
            //fill into the array n times - horizontal scaling
            for (int pixel_repeat = 0; pixel_repeat < n; pixel_repeat++)
            {
                triples_array[pixel_pos_in_array] = triple;
                pixel_pos_in_array += 1;
            }
        }
    
        //print the array + padding to the output file n times - vertical scaling
        for (int scanline_repeat = 0; scanline_repeat < n; scanline_repeat++)
        {
            //Write out the array
            for (int pixel_out = 0; pixel_out < bi2.biWidth; pixel_out++)
            {
                fwrite(&(triples_array[pixel_out]), sizeof(RGBTRIPLE), 1, outptr);
            }
            
            // print the needed padding for the line in the output file
            for (int k = 0; k < padding2; k++)
            {
                fputc(0x00, outptr);
            }
            
        }

        // skip to the next line over any padding in the input file, if any
        fseek(inptr, padding, SEEK_CUR);

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
