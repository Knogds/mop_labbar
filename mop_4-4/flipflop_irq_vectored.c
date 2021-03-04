#include "flipflop_irq_vectored.h"
#include "hw/gpio.h"
#include "hw/interrupt.h"
#include "hw/syscfg.h"

#define IRQ1      (1<<0)
#define IRQ2      (1<<1)
#define IRQCLK    (1<<2)
#define IRQACTIVE (1<<3)
#define IRQ1RST   (1<<4)
#define IRQ2RST   (1<<5)
#define IRQCLKRST (1<<6)
#define IRQ_RST_ALL IRQ1RST|IRQ2RST|IRQCLKRST

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

int hex_display = 0;

int main(void)
{
    init_app();

    while(1){
    }
    
    return 0;
}

static void init_app(void)
{
    *SCB_VTOR = VECTOR_TABLE_BASE;
    *EXTI0_HANDLER = exti0_irq_handler;   
    *EXTI1_HANDLER = exti1_irq_handler;
    *EXTI2_HANDLER = exti2_irq_handler;
 
    *GPIOD_MODER = 0x55555555; /* Out */
    
    *GPIOD_OTYPER = 0; /* push-pull (reset state) */
    
    *GPIOD_OSPEEDR = 0; /* low speed (reset state) */
    
    /* Connected to ext. interrupt hardware */
    *GPIOE_MODER = 0x00005500;  /* [7:4] Out [3:0] In */
    
    *GPIOE_PUPDR = 0x000000aa;  /* [15:4] No pull-up/down [3:0] Pull-down */

    /* SYSCFG_EXTICR1: external interrupt configuration register 1,
       select the source input for the EXTI0-3 external interrupt. */
    *SYSCFG_EXTICR1 &= ~(EXTI0(EXTI_MASK_ALL)
                        |EXTI1(EXTI_MASK_ALL)
                        |EXTI2(EXTI_MASK_ALL));


    *SYSCFG_EXTICR1 |= EXTI0(EXTIPORTE)
                      |EXTI1(EXTIPORTE)
                      |EXTI2(EXTIPORTE);

    /* Interrupt mask register unmask lines 2,1,0 */
    *EXTI_IMR |= GPIO2|GPIO1|GPIO0; 
                 
    /* Rising trigger enable */ 
    *EXTI_RTSR |= GPIO2|GPIO1|GPIO0;

    /* Falling edge disable (reset state: 0) */
    *EXTI_FTSR &= ~(GPIO2|GPIO1|GPIO0);

    /* Nested vectored interrupt controller */
    *NVIC_ISER(0) |= IRQ_EXTI2|IRQ_EXTI1|IRQ_EXTI0;

    /* reset external hardware */                                
    rst_hw_irq(IRQ_RST_ALL);
}

static void exti0_irq_handler()
{
    *EXTI_PR |= GPIO0;   /* Pending register,
                             1: selected trigger request occurred
                             This bit is set when the selected edge event
                             arrives on the external interrupt line.
                             This bit is cleared by programming it to ‘1’.*/

    if(hex_display > 0xff)
        hex_display = 0;
    else
        hex_display++;
        
    *GPIOD_ODR = hex_display;

    rst_hw_irq(IRQ1RST);
}

static void exti1_irq_handler()
{
    *EXTI_PR |= GPIO1;
    
    hex_display = 0;

    *GPIOD_ODR = hex_display;
    
    rst_hw_irq(IRQ2RST);
}

static void exti2_irq_handler()
{
    *EXTI_PR |= GPIO2;

    if (hex_display != 0xff)
        hex_display = 0xff;
    else
        hex_display = 0;

    
    *GPIOD_ODR = hex_display;

    rst_hw_irq(IRQCLKRST);
}

void rst_hw_irq(unsigned int irqrst)
{
    *GPIOE_ODR |= irqrst;
    *GPIOE_ODR &= ~irqrst;
}