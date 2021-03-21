/*
 * libMD407.h
 */

#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>

/* Type definitions */
#include <sys/stat.h>

typedef struct {
    char name[16];
    int (*init) (int);
    void (*deinit) (int);
    int (*fstat)(struct stat *st);
    int (*isatty)(void);
    int (*open)(const char name,int flags,int mode);
    int (*close)(void);
    int (*lseek)(int ptr, int dir);
    int (*write)(char *ptr, int len);
    int (*read)(char *ptr, int len);
} DEV_DRIVER_DESC, *PDEV_DRIVER_DESC;

typedef struct tag_usart{
    /* status register */
    volatile unsigned short sr;
    volatile unsigned short unused0;
    /* dataregister, holds latest received character *or* character to send */
    volatile unsigned short dr;
    volatile unsigned short unused1;
    volatile unsigned short brr;
    volatile unsigned short unused2;
    volatile unsigned short cr1;
    volatile unsigned short unused3;
    volatile unsigned short cr2;
    volatile unsigned short unused4;
    volatile unsigned short cr3;
    volatile unsigned short unused5;
    volatile unsigned short gtpr;
} usart;

typedef struct tag_gpio{
    volatile unsigned int moder;
    volatile unsigned int otyper;
    volatile unsigned int ospeedr;
    volatile unsigned int pupdr;
    volatile unsigned int idr;
    volatile unsigned int odr;
    volatile unsigned int bsrr;
    volatile unsigned int lckr;
    volatile unsigned int afrl;
    volatile unsigned int afrh;
} gpio;

/* File handle constants */
enum {STDIN=0,STDOUT,STDERR,KEYPAD,ASCIIDISPLAY};

#define MAX_FILENO ASCIIDISPLAY

/* Library defined functions */
int _isatty(int file);