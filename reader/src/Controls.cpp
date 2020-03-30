#include "Controls.h"

Controls::Controls()
{
    // Get Serial Pointer
    mSerPointer = mSerPointer->GetMySerial();
}

bool Controls::Init()
{
    if ( !bcm2835_init() )
    {
        return false;
    }

    // Set Green LED
    bcm2835_gpio_fsel(PIN_GREEN_LIGHT, BCM2835_GPIO_FSEL_OUTP);
    // Set Green Button
    bcm2835_gpio_fsel(PIN_GREEN_BUTTON, BCM2835_GPIO_FSEL_INPT);
    //  Set Green button as pullup
    bcm2835_gpio_set_pud(PIN_GREEN_BUTTON, BCM2835_GPIO_PUD_UP);
    //  Set Green button OFF
    bcm2835_gpio_write(PIN_GREEN_LIGHT, LOW);

    // Set Yellow LED
    bcm2835_gpio_fsel(PIN_YELLOW_LIGHT, BCM2835_GPIO_FSEL_OUTP);
    // Set Down Button
    bcm2835_gpio_fsel(PIN_DOWN_BUTTON, BCM2835_GPIO_FSEL_INPT);
    //  Set Down button as pullup
    bcm2835_gpio_set_pud(PIN_DOWN_BUTTON, BCM2835_GPIO_PUD_UP);
    //  Set Yellow button OFF
    bcm2835_gpio_write(PIN_YELLOW_LIGHT, LOW);

    // Set Red LED
    bcm2835_gpio_fsel(PIN_RED_LIGHT, BCM2835_GPIO_FSEL_OUTP);
    // Set Up Button
    bcm2835_gpio_fsel(PIN_UP_BUTTON, BCM2835_GPIO_FSEL_INPT);
    //  Set Up button as pullup
    bcm2835_gpio_set_pud(PIN_UP_BUTTON, BCM2835_GPIO_PUD_UP);
    //  Set Red button OFF
    bcm2835_gpio_write(PIN_RED_LIGHT, LOW);

    mLcd = new Lcd();
    mLcd->Init();

    return true;
}

void Controls::DeInit()
{
    bcm2835_close();
    delete mLcd;
}

void* Controls::Start(void* obj)
{
    ((Controls *) obj)->Start();
    return obj;
}

void Controls::Start()
{
	mStageStack.push(STARTUP);
    std::string str;
    while (1)
    {
        if ( 0 == bcm2835_gpio_lev(PIN_GREEN_BUTTON) )
        {
			std::cout<<"start button pressed"<<std::endl;
			mLcd->InitialDisplay();
            bcm2835_gpio_write(PIN_GREEN_LIGHT, HIGH);
			if ( STARTUP == mStageStack.top() )
			{
				sleep(1); // allow current to go back to 1, read event not working in this kernel
				PerformAction();
			}
        }
    }
};

void Controls::PerformAction()
{
    while (1)
    {
        if ( 0 == bcm2835_gpio_lev(PIN_GREEN_BUTTON) )
        {
			std::cout<<"start button pressed again"<<std::endl;
			if ( 0x0 == mLcd->GetArrowLoc() )
			{
				mStageStack.push(CHECKOUT);
				PerformCheckOut();
				Read();
			}
			else
			{
				mStageStack.push(CHECKIN);
				PerformCheckIn();
			}
			sleep(1); // allow current to go back to 1, read event not working in this kernel
		}
	}
}

void Controls::Read()
{
    pthread_t GreenLedBlink;
    bool secondRead=true;
    while (1)
    {
   	    if ( true == mSerPointer->Read(mId) )
        {
            ShowId();
            pthread_create(&GreenLedBlink, NULL, Controls::GreenLedBlink, this);
            while (secondRead == true )
            {
   	            if ( true == mSerPointer->Read(mId) )
                {
                    ShowId();
                    secondRead=false;
                }
            }
            pthread_cancel(GreenLedBlink);
        }
        //bcm2835_gpio_write(PIN_GREEN_LIGHT, LOW);
	}
}

void Controls::PerformCheckOut()
{
	mLcd->CheckInOut(0x0);
}

void Controls::PerformCheckIn()
{
	mLcd->CheckInOut(0x1);
}

void* Controls::CheckUpButton(void* obj)
{
    ((Controls *) obj)->CheckUpButton();
    return obj;
}

void Controls::CheckUpButton()
{
    uint8_t value = 0;
    while (1)
    {
        // Read some data
        value = bcm2835_gpio_lev(PIN_UP_BUTTON);
        if ( 0 == value )
        {
            bcm2835_gpio_write(PIN_RED_LIGHT, HIGH);
			mLcd->ArrowUp();
            bcm2835_gpio_write(PIN_RED_LIGHT, LOW);
        }
    }
};

void* Controls::CheckDownButton(void* obj)
{
    ((Controls *) obj)->CheckDownButton();
    return obj;
}

void Controls::CheckDownButton()
{
    uint8_t value = 0;
    while (1)
    {
        // Read some data
        value = bcm2835_gpio_lev(PIN_DOWN_BUTTON);
        if ( 0 == value )
        {
            bcm2835_gpio_write(PIN_YELLOW_LIGHT, HIGH);
			mLcd->ArrowDown();
            bcm2835_gpio_write(PIN_YELLOW_LIGHT, LOW);
        }
    }
};

void* Controls::GreenLedBlink(void* obj)
{
    ((Controls *) obj)->GreenLedBlink();
    return obj;
}

void Controls::GreenLedBlink()
{
    while (1)
    {
        delay(500);
        bcm2835_gpio_write(PIN_GREEN_LIGHT, HIGH);
        delay(500);
        bcm2835_gpio_write(PIN_GREEN_LIGHT, LOW);
    }
};

void Controls::ShowId()
{
 	mLcd->ClearDisplay();
    mLcd->SendData((char*)mId.c_str(),0x0);
}

