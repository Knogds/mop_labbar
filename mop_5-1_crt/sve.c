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
#include "delay.h"
#include <gpio.h>
#include <stdint.h>

/* Type definitions */
#include <sys/stat.h>

#define PERIPH                  0x40000000
#define AHB1          (PERIPH +    0x20000)
#define GPIOE         (AHB1   +     0x1000)
#define GPIOE_MODER   (GPIOE  +        0x0)
#define GPIOE_OTYPER  (GPIOE  +        0x4)
#define GPIOE_OSPEEDR (GPIOE  +        0x8)
#define GPIOE_PUPDR   (GPIOE  +        0xC)
#define GPIOE_IDR     (GPIOE  +       0x10)
#define GPIOE_ODR     (GPIOE  +       0x14)
#define GPIO_MODER    (uint32_t *) GPIOE_MODER
#define GPIO_OTYPER   (uint32_t *) GPIOE_OTYPER
#define GPIO_OSPEEDR  (uint32_t *) GPIOE_OSPEEDR
#define GPIO_PUPDR    (uint32_t *) GPIOE_PUPDR
/* high bits, data on LCD */
#define DATA_ODR      (uint8_t *) (GPIOE_ODR+1)
#define DATA_IDR      (volatile uint8_t *) (GPIOE_IDR+1)
/* low bits, command bits on LCD */
#define COMMAND_ODR   (uint8_t *)  GPIOE_ODR

#define E       6
#define SELECT  2
#define RW      1
#define RS      0

enum {B_RS=1, B_RW=2, B_SELECT=4, B_CS1=8, B_CS2=0x10, B_RST=0x20, B_E=0x40};


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

//static int asciidisplay_init( int initval );
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

void delay_systick(uint32_t load)
{
    *SYSTICK_LOAD = load;
    *SYSTICK_VAL = 0;
    *SYSTICK_CTRL = 5;
    while((*SYSTICK_CTRL & (1<<16)) == 0){
        __asm__("nop");
    };
}


void ascii_ctrl_bit_set(uint8_t x)
{
    *COMMAND_ODR |= (1 << SELECT)|(1 << x);
}


void ascii_ctrl_bit_clear(uint8_t x)
{
    *COMMAND_ODR &= ~(1 << x);
    *COMMAND_ODR |= (1 << SELECT);
}


uint8_t ascii_read_controller(void) //Check
{
    uint8_t data;
    ascii_ctrl_bit_set(E);
    /* delay >360ns */
    delay_systick(0x85f);
    data = *DATA_IDR;
    ascii_ctrl_bit_clear(E);
    return data;
}

uint8_t ascii_read_status(void) //Check
{
    uint8_t data;
    *GPIO_MODER = 0x00005555;
    ascii_ctrl_bit_clear(RS);
    ascii_ctrl_bit_set(RW);
    data = ascii_read_controller();
    *GPIO_MODER = 0x55555555;
    delay_micro(43);
    return data;
}

void ascii_write_controller(uint8_t byte) //check
{
    /* delay >40ns */
    delay_systick(0xee);
    ascii_ctrl_bit_set(E);
    *DATA_ODR = byte;
    ascii_ctrl_bit_clear(E);
    /* delay >10ns */
    delay_systick(0x3c);
}

void ascii_write_cmd(uint8_t command) //Check
{
    ascii_ctrl_bit_clear(RS);
    ascii_ctrl_bit_clear(RW);
    ascii_write_controller(command);
}

void ascii_write_data(uint8_t data) // Check
{
    ascii_ctrl_bit_set(RS);
    ascii_ctrl_bit_clear(RW);
    ascii_write_controller(data);
}

void ascii_write_char(uint8_t c) //Check
{
    while(ascii_read_status() != 0){
        __asm__("nop");
    }
    delay_micro(8);
    ascii_write_data(c);
    delay_micro(43);
}

static void ascii_cmd( int initval)
{
    while ((ascii_read_status() & 0x80) == 0x80);
    delay_micro(8);
    ascii_write_cmd(initval);
    delay_micro(39);
}

static int asciidisplay_init( int initval ) 
{
    *GPIO_MODER = 0x55555555;
    
    ascii_cmd(0x38);    // Set rows and dots
    ascii_cmd(0xE);     // Activate cursor
	ascii_cmd(0x6);     // Entry mode
	ascii_cmd(0x1);     // Clear display
    
    return 0;
}

static void asciidisplay_deinit( int deinitval)
{
    *GPIO_MODER = 0x55555555;
}

static int asciidisplay_write(char *ptr, int len)
{
	for (int i = 0; i < len; i++)
		ascii_write_char(*ptr++);
	return len;
}

static void wait_for_disp(void)
{
	while ((ascii_read_status() & 0x80) == 0x80);
}














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
    /* Set all registers to their reset state */
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

static int usart_write(char *ptr, int len)
{
    while(len--)
        _outchar(*ptr++);
}

static int usart_read(char *ptr, int len){

}













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