
/* Implements structs for the CMYK and RGB colorspaces and
 * conversion functions between CMYK and RGB
 *
 * For CS50 pset4
 */

#include <stdint.h>
//#include "bmp.h"


/**
 * CMYKQUADRUPLE
 *
 * This structure describes a color consisting of components (0-100%)
 * of the subtractive color space Cyan, Magenta, Yellow and Key/Black.
 *
 */
typedef struct
{
    int  cmykCyan;
    int  cmykMagenta;
    int  cmykYellow;
    int  cmykBlack;
}
CMYKQUADRUPLE;


CMYKQUADRUPLE rgb2cmyk(RGBTRIPLE rgbt)
{
    //declare a CMYK for the conversion
    CMYKQUADRUPLE cmykq;
    
    //Normalize the RGB to 0..100
    int r_norm, g_norm, b_norm;
    
    r_norm = (int) (((float) rgbt.rgbtRed * 100.0) / 255.0);
    g_norm = (int) (((float) rgbt.rgbtGreen * 100.0) / 255.0);
    b_norm = (int) (((float) rgbt.rgbtBlue * 100.0) / 255.0);
    
    //Find the highest color intensity in the triplet
    int triplet_norm_max;
    
    triplet_norm_max = r_norm;
    
    if (g_norm > triplet_norm_max)
        triplet_norm_max = g_norm;
        
    if (b_norm > triplet_norm_max)
        triplet_norm_max = b_norm;
    
    //Calculate the Black component
    cmykq.cmykBlack = (100 - triplet_norm_max);
    
    //Calculate the Cyan component and scale by 100
    cmykq.cmykCyan = (int) (100.0 * ((100.0 - (float) r_norm - (float) cmykq.cmykBlack) / (100.0 - (float) cmykq.cmykBlack)));

    //Calculate the Magenta and scale by 100
    cmykq.cmykMagenta = (int) (100.0 * ((100.0 - (float) g_norm - (float) cmykq.cmykBlack) / (100.0 - (float) cmykq.cmykBlack)));
    
    //Calculate the Yellow and scale by 100
    cmykq.cmykYellow = (int) (100 * ((100.0 - (float) b_norm - (float) cmykq.cmykBlack) / (100.0 - (float) cmykq.cmykBlack)));
    
    //return the converted quadruplet
    return cmykq;
    
}