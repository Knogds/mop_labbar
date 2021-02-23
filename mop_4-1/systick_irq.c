
#include "systick_irq.h"

volatile int systick_flag;
volatile int delay_count;

int main(void)
{
    init_app();

    while(1){
        if(systick_flag)
            break;
        *GPIO_ODR_HIGH += 1;
    }

    *GPIO_ODR_LOW = 0;
    return 0;
}

void init_app(void)
{
    *SCB_VTOR = VECTOR_TABLE_BASE;
    *(void (**)(void)) SYSTICK_HANDLER = systick_irq_handler;   
    /* configure all I/O-s as output */
    *GPIO_MODER = 0x55555555;
    /* configure all outputs as push-pull (reset state) */
    *GPIO_OTYPER = 0;
    /* low speed on all GPIOs (reset state for port D)*/
    *GPIO_OSPEEDR = 0;
    
    *GPIO_ODR = 0;
    
    delay(DELAY_COUNT);

    *GPIO_ODR_LOW =0xff;
}

void delay(unsigned int n)
{
    delay_count = n;
    systick_flag = 0;
    delay_1mikro();
}

void delay_1mikro(void)
{
    *STK_CTRL &= ~ENABLE;
    *STK_LOAD = RELOAD_VALUE;
    *STK_VAL = 0;
    *STK_CTRL = SOURCE_CLK | TICKINT | ENABLE;
}

void systick_irq_handler(void)
{
    *STK_CTRL &= ~ENABLE;
    if(delay_count--)
        delay_1mikro();
    else
        systick_flag = 1;

}
