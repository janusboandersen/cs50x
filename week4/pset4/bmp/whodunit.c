/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"
#include "colorspace.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[1];
    char* outfile = argv[2];

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

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //Retain previous pixel with usable information as a sort of smoothing

        RGBTRIPLE retained_triple;

        //Set white pixel for default
        retained_triple.rgbtRed = 255;
        retained_triple.rgbtGreen = 255;
        retained_triple.rgbtBlue = 255;
        
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            CMYKQUADRUPLE quad;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            //Convert from the RGB color space to CMYK
            quad = rgb2cmyk(triple);

            //A red filter on top of Cyan will create something darker towards grayscale / black-ish, and leave the red.
            //Cyan is composed of high values of G and B, and no R.
            //So if there is some cyan, turn down the color of the G and B channels
            if (quad.cmykCyan > 1)
            {
                
                triple.rgbtGreen *= (1.0 - (1.5 * quad.cmykCyan / 100.0));  //proportional darkening
                triple.rgbtBlue *= (1.0 - (1.5 * quad.cmykCyan / 100.0));  //proportional darkening
                triple.rgbtRed = (triple.rgbtGreen + triple.rgbtBlue) / 2.0;  //Average the red channel to create grayscale-like picture
                
                //Set the retained trailing pixels
                retained_triple.rgbtRed = triple.rgbtRed;
                retained_triple.rgbtGreen = triple.rgbtGreen;
                retained_triple.rgbtBlue = triple.rgbtBlue;
            }
            else
            {
                //use the retained trailing last pixels
                triple.rgbtRed = retained_triple.rgbtRed;
                triple.rgbtGreen = retained_triple.rgbtGreen;
                triple.rgbtBlue = retained_triple.rgbtBlue;
            }

            // write the adjusted RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
