/*
 * libMD407
 * usart_driver.c
 * Read buffered USART driver
 * Drivers for STDIN, STDOUT and STDERR
 */

#include "libMD407.h"

/* USART types and constants definitions */

/* We will use just USART1 here */
#define USART1 ((usart *) 0x40011000)
/*
#define USART2 ((usart *) 0x40004400)
#define USART3 ((usart *) 0x40004800)
#define USART4 ((usart *) 0x40004c00)
 ... */

#define NVIC_USART1_ISER ((volatile unsigned int *) 0xe000e104)
#define NVIC_USART1_IRQ_BPOS (1<<5)
#define USART1_IRQVEC ((void (**)(void))0x2001c0d4)

#define SR_CTS  (1<<9)
#define SR_LBD  (1<<8)
#define SR_TXE  (1<<7)
#define SR_TC   (1<<6)
#define SR_RXNE (1<<5)
#define SR_IDLE (1<<4)
#define SR_ORE  (1<<3)
#define SR_NF   (1<<2)
#define SR_FE   (1<<1)
#define SR_PE   (1<<0)

#define CR1_OVER8  (1<<15)
#define CR1_UE     (1<<13)
#define CR1_M      (1<<12)
#define CR1_WAKE   (1<<11)
#define CR1_PCE    (1<<10)
#define CR1_PS     (1<<9)
#define CR1_PEIE   (1<<8)
#define CR1_TXEIE  (1<<7)
#define CR1_TCIE   (1<<6)
#define CR1_RXNEIE (1<<5)
#define CR1_IDELIE (1<<4)
#define CR1_TE     (1<<3)
#define CR1_RE     (1<<2)
#define CR1_RWU    (1<<1)
#define CR1_SBK    (1<<0)

#define CR2_LINEN (1<<14)
#define CR2_STOP  (1<<12)
#define CR2_CLKEN (1<<11)
#define CR2_CPOL  (1<<10)
#define CR2_CPHA  (1<<9)
#define CR2_LBCL  (1<<8)
#define CR2_LBDIE (1<<6)
#define CR2_LBDL  (1<<5)
#define CR2_ADD   (1<<0)

#define CR3_ONEBIT (1<<11)
#define CR3_CTSIE  (1<<10)
#define CR3_CTSE   (1<<9)
#define CR3_RTSE   (1<<8)
#define CR3_DMAT   (1<<7)
#define CR3_DMAR   (1<<6)
#define CR3_SCEN   (1<<5)
#define CR3_NACK   (1<<4)
#define CR3_HDSEL  (1<<3)
#define CR3_IRLP   (1<<2)
#define CR3_IREN   (1<<1)
#define CR3_EIE    (1<<0)
    
static struct circ_buf {
    unsigned short size;
    unsigned short readpos;
    unsigned short writepos;
    unsigned short charstosend;
    char *outbuf;
};

/* Define functions here */
static void _outchar(char);
static char _tstchar(void);
static char _inchar(void);
static void fifo_check_free(struct circ_buf *);
static void usart_outchar(char);
static char usart_tstchar(void);
static void usart_irq_routine(void);
static int usart_init(int);
static void usart_deinit(int);
static int usart_write(char *, int);
static int usart_read(char *, int);

static struct circ_buf *fifo;
static char inbuf;

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

static void fifo_reset(struct circ_buf *buf)
{
    buf->writepos = 0;
    buf->readpos = buf->size;
}
static void fifo_check_free(struct circ_buf *buf)
{
    /* if readpos == writepos it is full */
    if(buf->readpos == buf->writepos){
        buf->writepos = 0;
        buf->readpos = buf->size;
    }
}

static int usart_init(int initval)
{   
    static int initialized;
    if( ! initialized){
        fifo->size = 256;
        fifo->outbuf = (char *) malloc(fifo->size);
        fifo->readpos = fifo->size;
        fifo->writepos = 0;
        fifo->charstosend = 0;
        
        /* configure 115200baud for 168MHz */
        USART1->brr = 0x02d9;
        /* erase control registers */
        USART1->cr2 = 0;
        USART1->cr3 = 0;
        /* RXNEIE: An USART interrupt is generated
         * TE: Transmitter enable
         * RE: Receiver enable
         * UE: USART enable */
        USART1->cr1 = CR1_UE | CR1_RXNEIE | CR1_TE | CR1_RE;
        
        /* configure interrupt */
        *((void (**)(void)) USART1_IRQVEC) = usart_irq_routine;
        *((unsigned int *) NVIC_USART1_ISER) |= NVIC_USART1_IRQ_BPOS;
        initialized = 1;
    }
    return 0;
}

static int usart_error(usart *u)
{
    /* error if one of USART_SR [3:0] is active */
    if(u->sr & 0xf)
        return 1;
    return 0;
}

static void usart_deinit(int deinitval)
{
    free(fifo->outbuf);
    /* unconfigure interrupt */
    *(void (**)(void)) USART1_IRQVEC = NULL;
    *(unsigned int *) NVIC_USART1_ISER = 0;
    
    /* reset registers */
    USART1->brr = 0;
    USART1->cr1 = 0;
    USART1->cr2 = 0;
    USART1->cr3 = 0;
}

static void write_outbuf()
{
    fifo_check_free(fifo);
    if(fifo->readpos != fifo->writepos){
        
        if(fifo->readpos == fifo->size)
            fifo->readpos = 0;
            
        fifo->charstosend--;
        
        USART1->dr = (unsigned short) fifo->outbuf[fifo->readpos++];
    
    }
    
    if(fifo->charstosend == 0){
        fifo_reset(fifo);
        USART1->cr1 &= ~CR1_TXEIE;
    }
}

static void usart_irq_routine(void)
{
    /* write */
    if((USART1->cr1 & CR1_TXEIE) && (USART1->sr & SR_TXE)){
        write_outbuf();
    }
    
    /* read */
    if(USART1->sr & SR_RXNE){
        inbuf = USART1->dr;
    }
}

/* _write for USART1 */
static int usart_write(char *ptr, int len)
{
    fifo_check_free(fifo);
            
    while(fifo->readpos != fifo->writepos && *ptr){
        
        if(fifo->writepos == fifo->size)
            fifo->writepos = 0;

        fifo->outbuf[fifo->writepos++] = *ptr++;
    }
    
    fifo->charstosend += len;
    
    USART1->cr1 |= CR1_TXEIE;
    
    return 0;
}

/* _read for USART1 */
static int usart_read(char *ptr, int len)
{
    char c = inbuf;
    inbuf = 0;

    if(c != 0){
        *ptr = c;
        return 1;
    }
    
    return 0;
}