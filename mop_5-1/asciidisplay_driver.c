/*
 * libMD407
 * asciidisplay_driver.c
 * Display connected to PE
 * Driver for ASCIIDISPLAY
 */

#include "libMD407.h"

static int asciidisplay_init( int initval );
static void asciidisplay_deinit( int deinitval);
static int asciidisplay_write(char *ptr, int len);

DEV_DRIVER_DESC AsciiDisplay =
{
    {"AsciiDisplay"},
    asciidisplay_init,
    asciidisplay_deinit,
    0,
    0,
    0,
    0,
    0,
    asciidisplay_write,
    0
};

/* ASCIIDISPLAY types and constants definitions */

// ...

/* Define functions here */

static int asciidisplay_init( int initval ){ ... }
static void asciidisplay_deinit( int deinitval){ ... }
static int asciidisplay_write(char *ptr, int len){ ... }
