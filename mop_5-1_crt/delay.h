#define SYSTICK                                 0xE000E010
#define SYSTICK_CTRL  (volatile unsigned int *) (SYSTICK + 0x0)
#define SYSTICK_LOAD  (volatile unsigned int *) (SYSTICK + 0x4)
#define SYSTICK_VAL   (volatile unsigned int *) (SYSTICK + 0x8)
#define SIMULATOR 1
#define COUNTFLAG 16

void delay_250ns(void)
{
    *SYSTICK_LOAD = 0x29;
    *SYSTICK_VAL = 0;
    *SYSTICK_CTRL = 5;
    while((*SYSTICK_CTRL & (1<<COUNTFLAG)) == 0){
        __asm__("nop");
    };
}

void delay_micro(unsigned int us)
{
#if SIMULATOR
    us = us/1000;
    us++;
#endif
    for(unsigned int i=0; i < us; i++)                                              
        for(unsigned char j=0; j < 4; j++)                                            
            delay_250ns();
}

void delay_milli(unsigned int ms)
{
    for(unsigned int i=0; i < ms; i++)
        delay_micro(1000);
}