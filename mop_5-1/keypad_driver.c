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

/* TODO */

/* Define functions here */

static int keypad_init( int initval ){ ... }
static void keypad_deinit( int deinitval){ ... }
static int keypad_read(char *ptr, int len){ ... }
