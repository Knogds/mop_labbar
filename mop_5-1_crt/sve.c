/*
 * libMD407
 * asciidisplay_driver.c
 * Display connected to PE
 * Driver for ASCIIDISPLAY
 */

// (#include "libMD407.h")// (#include "libMD407.h")// (#include "libMD407.h")
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

/* File handle constants */
enum {STDIN=0,STDOUT,STDERR,KEYPAD,ASCIIDISPLAY};

#define MAX_FILENO ASCIIDISPLAY

/* Library defined functions */
int _isatty(int file);
// (#include "libMD407.h")// (#include "libMD407.h")// (#include "libMD407.h")

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

static int asciidisplay_init( int initval ){/* TODO */}
static void asciidisplay_deinit( int deinitval){/* TODO */}
static int asciidisplay_write(char *ptr, int len){/* TODO */}
















/*
 * libMD407
 * general.c
 * includes: _crt_init, _crt_deinit, _sbrk for malloc-support.
 */

/////////////////////////////////////// #include "libMD407.h"

extern DEV_DRIVER_DESC StdIn, StdOut, StdErr, KeyPad, AsciiDisplay;

PDEV_DRIVER_DESC device_table[MAX_FILENO+1] = {
    &StdIn,
    &StdOut,
    &StdErr,
    &KeyPad,
    &AsciiDisplay,
};

static char *heap_end;
extern char __heap_low; /* Defined by the linker */
extern char __heap_top; /* Defined by the linker */

char * _sbrk(int incr) {

    char *prev_heap_end;

    if (heap_end == 0) {
        heap_end = &__heap_low;
    }

    prev_heap_end = heap_end;

    if (heap_end + incr > &__heap_top) {
        return (char *)-1;
    }

    heap_end += incr;

    return (char *) prev_heap_end;
}

__attribute__ ((used)) /* Will be optimised away otherwise... */

volatile void _crt_init() {
extern char __bss_start__; /* Defined by the linker */
extern char __bss_end__;   /* Defined by the linker */
    char *s;

    PDEV_DRIVER_DESC fd;

    heap_end = 0;

    /* NOTE: While testing, you may want to comment out the following four
       lines as they take a lot of time to run in the simulator. */
    s = &__bss_start__;
    while( s < &__bss_end__ ) *s++ = 0;
    s = &__heap_low;
    while( s < &__heap_top ) *s++ = 0;

    for( int i = 0; i <= MAX_FILENO; i++ )
    {
        fd = device_table[i];

        if( fd && fd->init != 0)
            (void) fd->init( 0 );
    }
}

__attribute__ ((used)) /* Will be optimised away otherwise... */
volatile void _crt_deinit() {
    PDEV_DRIVER_DESC fd;
    fflush(0); /* Will cause terminal flush... */
    for( int i = 0; i <= MAX_FILENO; i++ )
    {
        fd = device_table[i];
        if( fd && fd->deinit != 0)
            fd->deinit( 0 );
    }
}

/* STDIO-templates */
int _close(int file) { return -1; }
int _open(const char *name, int flags, int mode) { return -1; }
int _fstat(int file, struct stat *st) { st->st_mode = S_IFCHR; return 0; }
int _lseek(int file, int ptr, int dir) { return 0;}

int _isatty(int file) {
    switch (file)
    {
        case STDIN: case STDOUT: case STDERR: return 1;
        default: return 0;
    }
}

int _write(int file, char *ptr, int len) {
    PDEV_DRIVER_DESC drvr;
    drvr = device_table[file];
    if(drvr == 0)
        return 0;
    return drvr->write(ptr, len);
}

int _read(int file, char *ptr, int len) {
    PDEV_DRIVER_DESC drvr;
    drvr = device_table[file];
    if(drvr == 0)
        return 0;
    return drvr->read(ptr, len);
}





























/*
 * libMD407
 * keypad_driver.c
 * Keypad connected to PD8-PD15
 * Driver for KEYPAD
 */

/////////////////////////////////////// #include "libMD407.h"

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
typedef struct{
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

#define GPIOD ((gpio *) 0x40020c00)
/* Define functions here */

static int keypad_init( int initval )
{
    /* b11..b8 are inputs, the rest outputs */
    GPIOD->moder = 0x55005555;
    /* configure all outputs as push-pull (reset state) */
    GPIOD->otyper = 0;
    /* configure inputs as pull-down */
    GPIOD->pupdr = 0x00aa0000;
    /* low speed on all GPIOs (reset state for port D)*/
    GPIOD->ospeedr = 0;
}

static void keypad_deinit(int deinitval){
    /* Set all register to their reset state */
    GPIOD->moder = 0;
    GPIOD->otyper = 0;
    GPIOD->pupdr = 0;
    GPIOD->ospeedr = 0;
}

static int keypad_read(char *ptr, int len){
    
}



























/*
 * libMD407
 * usart_driver.c
 * Read buffered USART driver
 * Drivers for STDIN, STDOUT and STDERR
 */

/////////////////////////////////////// #include "libMD407.h"

/* USART types and constants definitions */

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

/* We will use just USART1 here */
#define USART1 ((usart *) 0x40011000)
#define USART2 ((usart *) 0x40004400)
#define USART3 ((usart *) 0x40004800)
#define USART4 ((usart *) 0x40004c00)
/* ... */

#define NVIC_USART1_ISER ((volatile unsigned int *) 0xe000e104)
#define NVIC_USART1_IRQ_BPOS (1<<5)
#define USART1_IRQVEC ((void (**)(void))0x2001c0d4)

/* Bits in USART CR1 register offset 0xc*/
#define BIT_EN (1<<13)    /* USART enable */
#define BIT_TXEIE (1<<7)  /* TXE interrupt enable */
#define BIT_TCIE (1<<6)   /* TC Interrupt enable */
#define BIT_RXNEIE (1<<5) /* RXNE interrupt enable */
#define BIT_TE (1<<3)     /* Transmitter enable */
#define BIT_RE (1<<2)     /* Receiver enable */

/* Bits in status register offset 0 */
#define BIT_RXNE (1<<5)   /* Receive data register full */
/* Bit 7 TXE holds 1 if TDR is empty, 0 if transmitting.
 * BIT_TXE is erased when writing to DR */
#define BIT_TXE (1<<7)

/* Define functions here */
static void _outchar(char);
static char _tstchar(void);
static char _inchar(void);
static void usart_outchar(char);
static char usart_tstchar(void);
static void usart_init(void);
static void usart_irq_routine(void);
//static int usart_init(int);
static void usart_deinit(int);
static int usart_write(char*, int);
static int usart_read(char *, int);

char inbuf, outbuf;

DEV_DRIVER_DESC StdIn =
{
    {"stdin"},
    usart_init,
    usart_deinit,
    0,
    _isatty,
    0,
    0,
    0,
    0,
    usart_read
};

DEV_DRIVER_DESC StdOut =
{
    {"stdout"},
    usart_init,
    usart_deinit,
    0,
    _isatty,
    0,
    0,
    0,
    usart_write,
    0
};

DEV_DRIVER_DESC StdErr =
{
    {"stderr"},
    usart_init,
    usart_deinit,
    0,
    _isatty,
    0,
    0,
    0,
    usart_write,
    0
};

/* USART implementation */

static void _outchar(char c)
{
    while ((USART1->sr & BIT_TXE) == 0);
    USART1->dr = (unsigned short) c;
}

static char _tstchar(void)
{
    if((USART1->sr & BIT_RXNE) == 0)
        return 0;
    return (char) USART1->dr;
}

static char _inchar(void)
{
    char c;
    while((c=_tstchar())==0);
    return c;
}

static void usart_irq_routine(void)
{
    if((USART1->cr1 & BIT_TXEIE) && (USART1->sr & BIT_TXE))
    {
        USART1->dr = (unsigned short) outbuf;
        USART1->cr1 &= ~BIT_TXEIE;
    }
    if(USART1->sr & BIT_RXNE)
        inbuf = (char) USART1->dr;
}

static int usart_error(usart *u)
{
    /* error if one of USART_SR [3:0] is active */
    if(u->sr & 0xf)
        return 1;
    return 0;
}

static void usart_init(void)
{
    /* configure interrupt */
    *(void (**)(void)) USART1_IRQVEC = usart_irq_routine;
    inbuf = 0;
    *(unsigned int *) NVIC_USART1_ISER |= NVIC_USART1_IRQ_BPOS;

    /* configure 115200baud for 168MHz */
    USART1->brr = 0x02d9;
    /* erase control registers */
    USART1->cr2 = 0;
    USART1->cr3 = 0;
    /* enable */
    USART1->cr1 = BIT_EN | BIT_RXNEIE | BIT_TE | BIT_RE;
}


static char usart_tstchar(void)
{
    char c = inbuf;
    inbuf = 0;
    return c;
}

static void usart_outchar(char c)
{
    outbuf = c;
    USART1->cr1 |= BIT_TXEIE;
}
    
static void usart_deinit(int deinitval)
{
    inbuf = 0;
    
    /* unconfigure interrupt */
    *(void (**)(void)) USART1_IRQVEC = NULL;
    *(unsigned int *) NVIC_USART1_ISER = 0;

    /* set the registers to their reset values */
    USART1->brr = 0;
    USART1->cr1 = 0;
    USART1->cr2 = 0;
    USART1->cr3 = 0;
}

static int usart_write(char *ptr, int len){/* TODO */}

static int usart_read(char *ptr, int len){/* TODO */}













////////////////////// M A L L O C    T E S T

int test_mem(void)
{
    char str0[] = "Test 0...";
    char str1[] = "Test 1...";
    char *s0, *s1;
    
    s0 = malloc(strlen(str0) + 1);

    if(!s0)
        return 1;

    strcpy(s0, str0);

    s1 = realloc(s0, strlen(str0) + 1 + strlen(str1) + 1);

    if(!s1)
        return 1;
    
    strcat(s1, str1);

    free(s1);
}



////////////////////// M A I N
int main(void)
{
     printf("Testing if stdout works on console. Check.\n");
     printf("Testing if stdin works on console. Type something:\n");
     char * input_text = (char *) malloc(64); 

     int i = 0; 
     while(1)
     {
        if(_read(STDIN, &input_text[i], 1)) {
            _write(STDOUT, &input_text[i], 1); 
            if(input_text[i] == '\n') {
                input_text[i+1] = '\0';
                break;
            }            
            i++;
        }
     }
     printf("What you typed should be on the ASCII display.\n");
     _write( ASCIIDISPLAY, input_text, strlen(input_text));
     free(input_text); 
     printf("Now press keys on the keypad and they should be repeated here.\n");
     
     char c;
     while( 1 )
     {
        if( _read( KEYPAD, &c, 1))
        {
            c += '0';
            _write( STDOUT, &c, 1);
        }
     }    
    return 0;
}