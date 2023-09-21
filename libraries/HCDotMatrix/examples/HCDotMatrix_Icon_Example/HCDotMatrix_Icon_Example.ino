/* FILE:    HCDotMatrix_Icon_Example
   DATE:    5/9/17
   VERSION: 0.1
   AUTHOR:  Andrew Davies


5/9/17 version 0.1: Original version

This sketch demonstrates how to use the HCDotMatrix Arduino library to display 
custom icons to the module. For suitable modules see item SKU HCOPTO0011 &
HCOPTO0067 in our store hobbycomponents.com

The HCDotMatrix library can be downloaded from the software section of our support
forum here:

http://forum.hobbycomponents.com/viewtopic.php?f=58


You may copy, alter and reuse this code in any way you like, but please leave
reference to HobbyComponents.com in your comments if you redistribute this code.
This software may not be used directly for the purpose of selling products that
directly compete with Hobby Components Ltd's own range of products.
THIS SOFTWARE IS PROVIDED "AS IS". HOBBY COMPONENTS MAKES NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ACCURACY OR LACK OF NEGLIGENCE.
HOBBY COMPONENTS SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR ANY DAMAGES,
INCLUDING, BUT NOT LIMITED TO, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY
REASON WHATSOEVER.
*/



// DIO pins used to drive module. Change the pin numbers to match your connections
#define ROW1  2    
#define ROW2  9    
#define ROW3  17    
#define ROW4  3   
#define ROW5  10 
#define ROW6  16
#define ROW7  11 
#define ROW8  12

#define COL1  6
#define COL2  13
#define COL3  14
#define COL4  4 
#define COL5  15
#define COL6  5
#define COL7  7
#define COL8  8


#include "HCDotMatrix.h"

byte Battery[][8] = {{0x00,0x7F,0xC1,0xC1,0xC1,0xC1,0x7F,0x00},   //Icon for 0% charge
                     {0x00,0x7F,0xC3,0xC3,0xC3,0xC3,0x7F,0x00},   //Icon for 20% charge
                     {0x00,0x7F,0xC7,0xC7,0xC7,0xC7,0x7F,0x00},   //Icon for 40% charge
                     {0x00,0x7F,0xCF,0xCF,0xCF,0xCF,0x7F,0x00},   //Icon for 60% charge
                     {0x00,0x7F,0xDF,0xDF,0xDF,0xDF,0x7F,0x00},   //Icon for 80% charge
                     {0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0x7F,0x00}};  //Icon for 100% charge


HCDotMatrix HCDotMatrix(ROW1,ROW2,ROW3,ROW4,ROW5,ROW6,ROW7,ROW8,  
                        COL1,COL2,COL3,COL4,COL5,COL6,COL7,COL8);

void setup() 
{
  //Initialise the library. If your module is a common anode type then change 
  //COMMON_CATHODE to COMMON_ANODE
  HCDotMatrix.init(COMMON_CATHODE);
}


void loop() 
{
  for(byte Icon = 0; Icon < 6; Icon++)  //Step through each icon frame.
  {
    for(byte i = 0; i < 8; i++)         //Write the current icon to the matrix buffer;
      HCDotMatrix.Buffer[i] = Battery[Icon][i];

     delay(500);
   }

}
