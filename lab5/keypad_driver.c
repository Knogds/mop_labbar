/*
 * libMD407
 * keypad_driver.c
 * Keypad connected to PD8-PD15
 * Driver for KEYPAD
 */

#include "libMD407.h"

static int keypad_init( int initval );
static void keypad_deinit( int deinitval);
static int keypad_read(char *ptr, int len);

DEV_DRIVER_DESC KeyPad =
{
    {"Keypad"},
    keypad_init,
    keypad_deinit,
    0,
    0,
    0,
    0,
    0,
    0,
    keypad_read
};

/* KEYPAD types and constants definitions */

#define GPIOD ((gpio *) 0x40020c00)
#define ROW_OUT (uint8_t *) (GPIOD->odr)
#define COL_IN (uint8_t *) (GPIOD->idr)
#define A 10
#define B 11
#define C 12
#define D 13
#define STAR 14
#define HASH 15

/* Define functions here */

static int keypad_init( int initval )
{
    /* b3..b0 are inputs, the rest outputs */
    GPIOD->moder = 0x55555500;
    /* configure all outputs as push-pull (reset state) */
    GPIOD->otyper = 0;
    /* configure inputs as pull-down */
    GPIOD->pupdr = 0x000000aa;
    /* low speed on all GPIOs (reset state for port D)*/
    GPIOD->ospeedr = 0;
    return 0;
}

static void keypad_deinit(int deinitval){
    /* Set all registers to their reset state */
    GPIOD->moder = 0;
    GPIOD->otyper = 0;
    GPIOD->pupdr = 0;
    GPIOD->ospeedr = 0;
}

/*
ROW_OUT: b4----1  2  3  A
         b5----4  5  6  B
         b6----7  8  9  C
         b7----*  0  #  D
               |  |  |  |
              b0 b1 b2 b3
COL_IN value:  1  2  4  8
*/
static uint8_t keyb(void)
{
    GPIOD->odr = (1<<4);
    if(GPIOD->idr == 1) return 1;
    if(GPIOD->idr == 2) return 2;
    if(GPIOD->idr == 4) return 3;
    if(GPIOD->idr == 8) return 0xa;
    GPIOD->odr = (1<<5);
    if(GPIOD->idr == 1) return 4;
    if(GPIOD->idr == 2) return 5;
    if(GPIOD->idr == 4) return 6;
    if(GPIOD->idr == 8) return 0xb;
    GPIOD->odr = (1<<6);
    if(GPIOD->idr == 1) return 7;
    if(GPIOD->idr == 2) return 8;
    if(GPIOD->idr == 4) return 9;
    if(GPIOD->idr == 8) return 0xc;
    GPIOD->odr = (1<<7);
    if(GPIOD->idr == 1) return 14;
    if(GPIOD->idr == 2) return 0;
    if(GPIOD->idr == 4) return 15;
    if(GPIOD->idr == 8) return 0xd;
    return 0xff;
}

static int keypad_read(char *ptr, int len)
{
    char out = keyb();

    if(out<=0xf){
        *ptr=out;
        return 1;
    }
    return 0;
}