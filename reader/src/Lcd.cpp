#include "Lcd.h"

void Lcd::Init()
{
    short flag=1;
    // Set LED RS
    bcm2835_gpio_fsel(LCD_RS, BCM2835_GPIO_FSEL_OUTP);
    // Set LED RW
    bcm2835_gpio_fsel(LCD_RW, BCM2835_GPIO_FSEL_OUTP);
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

    // initialise LCD
    SendCmd(0x33); // full init 
    while ( flag == 1 )
    {
        flag = CheckBusyFlag();
    }
    SendCmd(0x32); // 4 bit mode
    SendCmd(0x28); // 2 line mode
    SendCmd(0x0C); // display on, cursor off, blink off
    SendCmd(0x01);  // clear screen

}

short Lcd::CheckBusyFlag()
{
    bcm2835_gpio_fsel(LCD_RW, BCM2835_GPIO_FSEL_INPT);
    int value = bcm2835_gpio_lev(LCD_RW);
    bcm2835_gpio_fsel(LCD_RW, BCM2835_GPIO_FSEL_OUTP);
    return value;
}

void Lcd::PulseEnable()
{
    bcm2835_gpio_write (LCD_E, HIGH) ; 
    delay(10); 
    bcm2835_gpio_write (LCD_E, LOW) ; 
}

//  send a byte to the lcd in two nibbles
//  before calling use SetChrMode or SetCmdMode to determine whether to send character or command
void Lcd::Lcd_Byte(char bits)
{
    bcm2835_gpio_write(LCD_D4,(bits & 0x10));
    bcm2835_gpio_write(LCD_D5,(bits & 0x20));
    bcm2835_gpio_write(LCD_D6,(bits & 0x40));
    bcm2835_gpio_write(LCD_D7,(bits & 0x80)); 
    PulseEnable();
    delay(1000); 

    bcm2835_gpio_write(LCD_D4,(bits & 0x1));  
    bcm2835_gpio_write(LCD_D5,(bits & 0x2));
    bcm2835_gpio_write(LCD_D6,(bits & 0x4));
    bcm2835_gpio_write(LCD_D7,(bits & 0x8));
    PulseEnable();
    delay(1000); 

}

void Lcd::SendCmd( char cmd ) 
{
    bcm2835_gpio_write (LCD_RS, LOW) ; 
    bcm2835_gpio_write (LCD_RW, LOW) ; 
    Lcd_Byte(cmd);
}

void Lcd::SendData(char *s) 
{
    while(*s)
    {
        bcm2835_gpio_write (LCD_RS, HIGH) ; 
        bcm2835_gpio_write (LCD_RW, LOW) ; 
	    Lcd_Byte(*s++);
    }
}

