#include "Lcd.h"

void Lcd::Init()
{
	
    // Set LED BL
    bcm2835_gpio_fsel(LCD_BL, BCM2835_GPIO_FSEL_OUTP);
    // Set LED RS
    bcm2835_gpio_fsel(LCD_RS, BCM2835_GPIO_FSEL_OUTP);
    // Set LED E
    bcm2835_gpio_fsel(LCD_E, BCM2835_GPIO_FSEL_OUTP);
    // Set LED D4
    bcm2835_gpio_fsel(LCD_D4, BCM2835_GPIO_FSEL_OUTP);
    // Set LED D5
    bcm2835_gpio_fsel(LCD_D5, BCM2835_GPIO_FSEL_OUTP);
    // Set LED D6
    bcm2835_gpio_fsel(LCD_D6, BCM2835_GPIO_FSEL_OUTP);
    // Set LED D7
    bcm2835_gpio_fsel(LCD_D7, BCM2835_GPIO_FSEL_OUTP);

    SendCmd(0x33); // Init 
    SendCmd(0x32); // 4-bit
    SendCmd(0x06); // Increment Address by 1, Shift cursor to right
    SendCmd(0x0C); // Display ON, Cursor ON, Cursor Blinking
    SendCmd(0x28); 
    SendCmd(0x02); // Return to home
	ClearDisplay();
    delay(2); 
	bcm2835_gpio_write(LCD_BL, LOW);
	InitMessages();
}

void Lcd::PulseEnable()
{
    delay(0.5); 
    bcm2835_gpio_write (LCD_E, HIGH); 
    delay(0.5); 
    bcm2835_gpio_write (LCD_E, LOW); 
    delay(0.5); 
}

void Lcd::Lcd_Byte(char bits)
{
	ClearBits();

	if ( bits & 0x10 )
	{
    	bcm2835_gpio_write(LCD_D4,HIGH);
	}
	if ( bits & 0x20 )
	{
    	bcm2835_gpio_write(LCD_D5,HIGH);
	}
	if ( bits & 0x40 )
	{
    	bcm2835_gpio_write(LCD_D6,HIGH);
	}
	if ( bits & 0x80 )
	{
    	bcm2835_gpio_write(LCD_D7,HIGH); 
	}

    PulseEnable();

	ClearBits();
	if ( bits & 0x1 )
	{
    	bcm2835_gpio_write(LCD_D4,HIGH);
	}
	if ( bits & 0x2 )
	{
    	bcm2835_gpio_write(LCD_D5,HIGH);
	}
	if ( bits & 0x4 )
	{
    	bcm2835_gpio_write(LCD_D6,HIGH);
	}
	if ( bits & 0x8 )
	{
    	bcm2835_gpio_write(LCD_D7,HIGH); 
	}
    PulseEnable();


}

void Lcd::SendCmd( char cmd ) 
{
    bcm2835_gpio_write (LCD_RS, LOW) ; 
    Lcd_Byte(cmd);
    delay(0.5); 
}

void Lcd::SendDataNoArrow(char *s) 
{
    bcm2835_gpio_write (LCD_RS, HIGH) ; 
    while(*s)
    {
	    Lcd_Byte(*s++);
    }

}

void Lcd::SendData(char *s, char inLine) 
{
    bcm2835_gpio_write (LCD_RS, HIGH) ; 
	if ( ! inLine ^ mArrowLoc ) // arrow is on this line
	{
    	SendSpecChar(0x7E); // arrow 
    	SendSpecChar(0x10); // space
	}
	else // arrow not on this line
	{
    	SendSpecChar(0x10); // space
    	SendSpecChar(0x10); // space
	}
    while(*s)
    {
	    Lcd_Byte(*s++);
    }
}

void Lcd::SendSpecChar(char bits) 
{
	bcm2835_gpio_write (LCD_RS, HIGH) ; 
	Lcd_Byte(bits);
}

void Lcd::ClearBits()
{
	bcm2835_gpio_write(LCD_D4,LOW);
	bcm2835_gpio_write(LCD_D5,LOW);
	bcm2835_gpio_write(LCD_D6,LOW);
	bcm2835_gpio_write(LCD_D7,LOW);
}

void Lcd::ClearDisplay()
{
    SendCmd(0x01); 
    delay(2); 
}

void Lcd::InitialDisplay()
{
	mArrowLoc=0x0;
	bcm2835_gpio_write(LCD_BL, HIGH);
    ClearDisplay();
	SendData((char*)mInitMessage[0].c_str(),0x0);
    SendCmd(0xC0);	// Next line
	SendData((char*)mInitMessage[1].c_str(),0x1);
}

void Lcd::CheckInOut(char s)
{
	mArrowLoc=0x0; // set arrown to first line
   	ClearDisplay();
	if ( 0x0 == s )
	{
		SendDataNoArrow((char*)mCheckOutMessage[0].c_str());
	}
	else
	{
		SendDataNoArrow((char*)mCheckOutMessage[1].c_str());
	}
}

void Lcd::InitMessages()
{
	mInitMessage.push_back("Check-Out");
	mInitMessage.push_back("Check-In");
	mCheckOutMessage.push_back("Scan Card Now");
	mCheckOutMessage.push_back("Scan Movie Now");
}

void Lcd::ArrowUp()
{
	if ( 1 == mArrowLoc ) // arrow on second line
	{
		mArrowLoc=0x0; // set arrown to first line
    	ClearDisplay();
		SendData((char*)mInitMessage[0].c_str(),0x0);
    	SendCmd(0xC0);	// Next line
		SendData((char*)mInitMessage[1].c_str(),0x1);
	}
	// else do nothing
}

void Lcd::ArrowDown()
{
	if ( 0 == mArrowLoc ) // arrow on first line
	{
		mArrowLoc=0x1; // set arrown to second line
    	ClearDisplay();
		SendData((char*)mInitMessage[0].c_str(),0x0);
    	SendCmd(0xC0);	// Next line
		SendData((char*)mInitMessage[1].c_str(),0x1);
	}
	// else do nothing

}

