#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define PIN_RED_LIGHT RPI_GPIO_P1_26
#define PIN_RED_BUTTON RPI_GPIO_P1_22
#define PIN_GREEN_LIGHT RPI_GPIO_P1_24
#define PIN_GREEN_BUTTON RPI_GPIO_P1_23
#define LCD_RW RPI_GPIO_P1_07
#define LCD_RS RPI_GPIO_P1_18
#define LCD_E RPI_GPIO_P1_16
#define LCD_D4 RPI_GPIO_P1_15
#define LCD_D5 RPI_GPIO_P1_13
#define LCD_D6 RPI_GPIO_P1_12
#define LCD_D7 RPI_GPIO_P1_11

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <bcm2835.h>
#include <pthread.h>
#include "MySerial.h"


#endif // DEFINITIONS_H

