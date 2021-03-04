#include "flipflop_irq.h"
#include "gpio.h"
#include "src/hw/interrupt.h"
#include "src/hw/syscfg.h"

/*
 * HW interrupt operates something like this:
 * 
 * inputs: b[3:0]
 * 
 *       O  IRQ IRQCLK IRQ2 IRQ1
 *  IRQ1 |  b3    b2    b1   b0
 * 
 *          b0 "hi" when IRQ1 activates
 *       O  b1 "hi" when IRQ2 activates
 *  IRQ2 |  b2 "hi" when IRQCLK activates
 *          b3 "hi" when IRQ1|IRQ2|IRQCLK activates
 *          b[3:0] turns off when IRQRST activates
 *
 *  IRQ  |   10Hz |    IRQ O
 *  CLK  O  100Hz O    RST |
 * 
 * outputs: b[7:4]
 * 
 * b4 rising edge resets IRQ1
 * b5 rising edge resets IRQ2
 * b6 rising edge resets IRQCLK
 * 
 */

int main(void)
{
    init_app();

    while(1){

    }
}

static void init_app(void)
{
    *SCB_VTOR = VECTOR_TABLE_BASE;
    *((void (**)(void)) EXTI3_HANDLER) = exti3_irq_handler;   
 
    *GPIOD_MODER = 0x55555555; /* Out */
    *GPIOD_OTYPER = 0; /* push-pull (reset state) */
    *GPIOD_OSPEEDR = 0; /* low speed (reset state) */
    
    /* Connected to ext. interrupt hardware */
    *GPIOE_MODER = 0x00005500;  /* [15:8] Out [7:0] In */
    *GPIOE_PUPDR = 0x000000aa;  /* [15:8] No pull-up/down [7:0] Pull-down */

    *SYSCFG_EXTICR1 &= ~0xf000; /* SYSCFG_EXTICR1: external interrupt
                                   configuration register 1 */
    *SYSCFG_EXTICR1 |= 0x4000;  /* select the source input for the EXTIx
                                   external interrupt.
                                   EXTI3[15:12] 0b0100, selects port E */ 
    *EXTI_IMR |= (1<<3);        /* Interrupt mask register
                                   1: Interrupt request from line 3
                                   is not masked */
    *EXTI_RTSR |= (1<<3);       /* Rising trigger enable */
    *EXTI_FTSR &= ~(1<<3);      /* Falling edge disable (reset state) */
    *NVIC_ISER0 |= (1<<9);      /* Nested vectored interrupt controller
                                   1: Enable interrupt */
}

static void exti3_irq_handler()
{
    static int hex_display;
    
    if(hex_display > 0xff)
        hex_display = 0;
    else
        hex_display++;

    *GPIOD_ODR = hex_display;
    
    *EXTI_PR |= (1<<3);   /* Pending register,
                             1: selected trigger request occurred */
}
