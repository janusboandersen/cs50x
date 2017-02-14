#include <cs50.h>
#include <stdio.h>

/* This program converts the number of minutes the user showers
* to an equivalent number of water bottles 
* Save water everyone!
*/

int main(void)
{

//define some basic physics conversion
float showerflow_gallons_per_minute = 1.5; //in gallons per minute
float gallons_to_ounces = 128.0; //1 gallon is 128 ounces
float bottle_volume_ounces = 16.0; //16 ounces of water in a bottle

//prompt the user for input
printf("Please enter your normal shower time in minutes? \n");
unsigned int showertime_minutes = GetInt();

//analyze and output the results
int bottle_equivalents;
bottle_equivalents = (int) (showertime_minutes * (showerflow_gallons_per_minute * gallons_to_ounces / bottle_volume_ounces)); //some rounding will occur when casting to an int)
printf("That is equivalent number of bottles %d\n", bottle_equivalents);

}