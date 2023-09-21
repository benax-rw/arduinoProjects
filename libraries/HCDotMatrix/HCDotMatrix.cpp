/* FILE:    HCDotMatrix.cpp
   DATE:    05/09/17
   VERSION: 2.0
   AUTHOR:  Andrew Davies
   WEBSITE: HobbyComponents.com


21/01/16 V0.1: Original version
05/09/17 V2.0: New version - complete rewrite of previous version.
		 	   Now refreshes the screen in the background using timer interrupt 2.
			   UpdateMatrix() function removed as no longer required.
			   Added init() function (must be run once at beginning of sketch).
			   print() function now supports printing of floating point numbers.
			   Added printChar() function allowing printing of single ASCII characters.
			   Added clear() function to clear the module buffer and display.
			   Added setLED() function to turn on an individual LED from an X/Y coordinate.
			   Added clearLED() function to turn off an individual LED from an X/Y coordinate.
			   Added getLED() function to get the current state of one of the modules LEDs.
			   Added invert() function to reverse the state of the LEDs.
					  

Library for driving 8x8 LED dot matrix modules. This Arduino library was written
to support the following Hobby Components product(s):

8x8 Red LED Matrix Module (HCOPTO0011)
8x8 Mini 20mm 8x8 Red LED Matrix (HCOPTO0067)

More information about this library can be found in the software section of our support 
forum here:

http://forum.hobbycomponents.com/software


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


#include "HCDotMatrix.h"

/* Timer 2 clock prescalling values */
enum HCT2PreScaller
{
	T2_CLK_DIV_0    = 1,
	T2_CLK_DIV_8    = 2,
	T2_CLK_DIV_32   = 3,
	T2_CLK_DIV_64   = 4,
    T2_CLK_DIV_128  = 5,
    T2_CLK_DIV_256  = 6,
    T2_CLK_DIV_1024 = 7
};


void HCTimer2Init(byte prescaler, byte compare);


/* Array to contain pointers to each instance of the library */
static HCDotMatrix* ptrRefresh[MAXMODULES]; 

/* Used to track how many instances of the library have been created */
byte NumOfInstances = 0;

/* Library constructor */
HCDotMatrix::HCDotMatrix(byte R1,byte R2,byte R3,byte R4,byte R5,byte R6,byte R7, byte R8,
		      byte C1,byte C2,byte C3,byte C4,byte C5,byte C6,byte C7, byte C8)
{  	
	/* Set the current LED to the top corner */
	_RowPos = 0;
	_ColPos = 0;
	
	/* Set all the row and column pins to outputs */
	pinMode(R1, OUTPUT);
	pinMode(R2, OUTPUT);
	pinMode(R3, OUTPUT);
	pinMode(R4, OUTPUT);
	pinMode(R5, OUTPUT);
	pinMode(R6, OUTPUT);
	pinMode(R7, OUTPUT);
	pinMode(R8, OUTPUT);
	
	pinMode(C1, OUTPUT);
	pinMode(C2, OUTPUT);
	pinMode(C3, OUTPUT);
	pinMode(C4, OUTPUT);
	pinMode(C5, OUTPUT);
	pinMode(C6, OUTPUT);
	pinMode(C7, OUTPUT);
	pinMode(C8, OUTPUT);
	
	
	/* Writing to pins using the Arduino digitalWrite() function is slow
	   so get the port and bit masks for each pin so we can directly write to
	   the ports */
	_Row_Pins[0].Port = portOutputRegister(digitalPinToPort(R1));
	_Row_Pins[0].Mask = digitalPinToBitMask(R1);
	_Row_Pins[1].Port = portOutputRegister(digitalPinToPort(R2));
	_Row_Pins[1].Mask = digitalPinToBitMask(R2);
	_Row_Pins[2].Port = portOutputRegister(digitalPinToPort(R3));
	_Row_Pins[2].Mask = digitalPinToBitMask(R3);
	_Row_Pins[3].Port = portOutputRegister(digitalPinToPort(R4));
	_Row_Pins[3].Mask = digitalPinToBitMask(R4);
	_Row_Pins[4].Port = portOutputRegister(digitalPinToPort(R5));
	_Row_Pins[4].Mask = digitalPinToBitMask(R5);
	_Row_Pins[5].Port = portOutputRegister(digitalPinToPort(R6));
	_Row_Pins[5].Mask = digitalPinToBitMask(R6);
	_Row_Pins[6].Port = portOutputRegister(digitalPinToPort(R7));
	_Row_Pins[6].Mask = digitalPinToBitMask(R7);
	_Row_Pins[7].Port = portOutputRegister(digitalPinToPort(R8));
	_Row_Pins[7].Mask = digitalPinToBitMask(R8);
	
	_Col_Pins[0].Port = portOutputRegister(digitalPinToPort(C1));
	_Col_Pins[0].Mask = digitalPinToBitMask(C1);
	_Col_Pins[1].Port = portOutputRegister(digitalPinToPort(C2));
	_Col_Pins[1].Mask = digitalPinToBitMask(C2);
	_Col_Pins[2].Port = portOutputRegister(digitalPinToPort(C3));
	_Col_Pins[2].Mask = digitalPinToBitMask(C3);
	_Col_Pins[3].Port = portOutputRegister(digitalPinToPort(C4));
	_Col_Pins[3].Mask = digitalPinToBitMask(C4);
	_Col_Pins[4].Port = portOutputRegister(digitalPinToPort(C5));
	_Col_Pins[4].Mask = digitalPinToBitMask(C5);
	_Col_Pins[5].Port = portOutputRegister(digitalPinToPort(C6));
	_Col_Pins[5].Mask = digitalPinToBitMask(C6);
	_Col_Pins[6].Port = portOutputRegister(digitalPinToPort(C7));
	_Col_Pins[6].Mask = digitalPinToBitMask(C7);
	_Col_Pins[7].Port = portOutputRegister(digitalPinToPort(C8));
	_Col_Pins[7].Mask = digitalPinToBitMask(C8);
	
	
	/* Set all row and column pins low */
	for(byte i = 0; i < 8; i++)
	{
		*_Row_Pins[_RowPos].Port &= ~_Row_Pins[_RowPos].Mask;
		*_Col_Pins[_ColPos].Port &= ~_Col_Pins[_ColPos].Mask;
	}
	
	/* Store a pointer to this instance of the library */
	ptrRefresh[NumOfInstances] = this;
	
	/* Add one to the library instance counter */
	if(NumOfInstances < MAXMODULES)
		NumOfInstances++;	
}



/* Initialises the library where:
   ModuleType is the type of module. Valid values are:
		COMMON_CATHODE = Dot matrix module is a common cathode type.
		COMMON_ANODE   = Dot matrix module is a common anode type. */
void HCDotMatrix::init(boolean ModuleType)
{
	/* Clear the display buffer */
	clear();
	
	/* Initialises the HCTimer2 library with a 128us interval */
	  HCTimer2Init(T2_CLK_DIV_8, 255);

	/* If the module type is a common anode then invert the display to flip the pin direction */
	if(ModuleType == COMMON_ANODE)
		_Invert = !_Invert;	
}



/* Prints a string of text to the module starting at a specified column position where:
   TextString[] is a character array containing the text to print.

   Offset is the column position from where the text will start from. Valid values are from 0 to 65535 (Uno/Nano etc) where:
	   1 = right most column
	   8 = left most column
	   
	   Values above 8 will start the text at a column beyond the left most column. */
#ifdef ENABLEFONT
void HCDotMatrix::print(char TextString[], unsigned int Offset)
{
	for(byte i = 0; i < strlen(TextString); i++)
	{
		if(Offset)
		{
			/* Print the next character in the text string */
			printChar(TextString[i], Offset);
		
			if(Offset >= 8)
				Offset -= 8;
			else
				Offset = 0;
		}
	}
}
#endif



/* Prints a floating point number to the module starting at a specified position where:
   Value is the number to print.

   Offset is the column position from where the value will start from. Valid values are from 0 to 65535 (Uno/Nano etc) where:
	   1 = right most column
	   8 = left most column
	   
	   Values above 8 will start the text at a column beyond the left most column. 
	   
   DP is an option value which specifies the number of decimal places to display a floating point number to. */
#ifdef ENABLEFONT
void HCDotMatrix::print(float Value, unsigned int Offset = 8, byte DP = 2)
{
	char sTemp[15];
	
	print(dtostrf(Value, 0, DP, sTemp), Offset);
}
#endif



/* Prints a single ASCII character to the module starting at a specified position where:
   Character is the ASCII character to print.

   Offset is the column position from where the character will start from. Valid values are from 0 to 65535 (Uno/Nano etc) where:
	   1 = right most column
	   8 = left most column
	   
	   Values above 8 will start the text at a column beyond the left most column. */
#ifdef ENABLEFONT
void HCDotMatrix::printChar(char Character, byte Offset = 8)
{
	byte StartIndex = 0, EndIndex = 7, ColIndex;

	/* Only characters starting at column 15 and below will appear on the module. */
	if(Offset < 16)
	{
		/* ASCII character must be printable ! */
		if(Character < ' ' || Character > '~')
			Character = ' ';
		
		/* Work out what columns of the character will appear on the module based on the character offset */
		if(Offset > 8)
		{
			EndIndex = 15 - Offset;
			ColIndex = Offset - 8;
		}else
		{
			StartIndex = 8 - Offset;
		}

		/* Write the visible columns to the module buffer */
		while(StartIndex <= EndIndex)
		{
			Buffer[StartIndex] = pgm_read_byte(&Font8x8[Character - 32][ColIndex]);
			StartIndex++;
			ColIndex++;	
		}
	}
}
#endif


/* Clears any data in the module buffer therefore turning off all LEDs on the module. */
void HCDotMatrix::clear(void)
{
	for(byte i = 0; i < 8; i++)
		Buffer[i] = 0;
}



/* Tuns on an LED at the specified X & Y coordinate where:
		X is the column coordinate (0 = left most & 7 = right most column)
		Y is the row coordinate (0 = top row & 7 = bottom row) */
void HCDotMatrix::setLED(byte X, byte Y)
{
	if(X < 8 && Y < 8)
		Buffer[X] |= 0x80 >> Y;
}



/* Tuns off an LED at the specified X & Y coordinate where:
		X is the column coordinate (0 = left most & 7 = right most column)
		Y is the row coordinate (0 = top row & 7 = bottom row) */
void HCDotMatrix::clearLED(byte X, byte Y)
{
	if(X < 8 && Y < 8)
		Buffer[X] &= ~(0x80 >> Y);
}



/* Gets the state of an LED at the specified X & Y coordinate where:
		X is the column coordinate (0 = left most & 7 = right most column)
		Y is the row coordinate (0 = top row & 7 = bottom row) 
		
   Returns a boolean true/false value representing the on/off state of the LED. */
boolean HCDotMatrix::getLED(byte X, byte Y)
{
	if(X < 8 && Y < 8)
		return (Buffer[X] >> (7 - Y)) & 0x01;
	else
		return false;
}


/* Inverts the on/off state of the LEDs */
void HCDotMatrix::invert(void)
{
	_Invert = !_Invert;
}



/* This function is executed via the timer interrupt. Turns off the current LED
   and sets the state of the next LED depending on its value in the module buffer */
void HCDotMatrix::refresh(void)
{	
	/* Turn off previous LED */
	*_Row_Pins[_RowPos].Port &= ~_Row_Pins[_RowPos].Mask;
	*_Col_Pins[_ColPos].Port |= _Col_Pins[_ColPos].Mask;

	
	/* Set row and column pointers to the next LED */
	_RowPos++;
	
	if(_RowPos == 8)
	{
		_RowPos = 0;
		_ColPos++;
		if(_ColPos == 8)
			_ColPos = 0;
	}

	
	/* Set the state of the next LED depending on its value in the module buffer */
	if(((Buffer[_ColPos] >> (7 - _RowPos)) & 0x01) ^ _Invert)
	{
		*_Row_Pins[_RowPos].Port |= _Row_Pins[_RowPos].Mask;
		*_Col_Pins[_ColPos].Port &= ~_Col_Pins[_ColPos].Mask;
	}
	else
	{
		*_Row_Pins[_RowPos].Port &= ~_Row_Pins[_RowPos].Mask;
		*_Col_Pins[_ColPos].Port |= _Col_Pins[_ColPos].Mask;
	}
}




/* Sets up the timer 2 interrupt so that the display can be refreshed in the background */
void HCTimer2Init(byte prescaler, byte compare)
{
	/* Turn off interrupts whilst we setup the timer */
	cli();
	/* Set timer mode to clear timer on compare match (mode 2)*/
	TCCR2A = (1<<WGM21);

	/* Set the prescaler */
	TCCR2B = prescaler;

	/* Clear timer 2 counter */
	TCNT2 = 0;

	/* Set the compare match register */
	OCR2A = compare;

	/* Enable timer 2 interrupt on compare match */
	TIMSK2 = (1<<OCIE2A);

  	/* Turn interrupts back on */
  	sei();
}



/* Interrupt service routine for Timer 2 compare match */
ISR(TIMER2_COMPA_vect)
{
	/* Runs the refresh() function for each instance of the library. */
	for(byte i = 0; i < NumOfInstances; i++)
		ptrRefresh[i]->refresh(); 
}