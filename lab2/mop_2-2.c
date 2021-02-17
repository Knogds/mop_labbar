#include <stdint.h>

#define PERIPH                  0x40000000
#define AHB1          (PERIPH +    0x20000)
#define GPIOD         (AHB1   +      0xC00)
#define GPIOD_MODER   (GPIOD  +        0x0)
#define GPIOD_OTYPER  (GPIOD  +        0x4)
#define GPIOD_OSPEEDR (GPIOD  +        0x8)
#define GPIOD_ODR     (GPIOD  +       0x14)

#define SYSTICK                                 0xE000E010
#define SYSTICK_CTRL  (volatile uint32_t *) (SYSTICK + 0x0)
#define SYSTICK_LOAD  (volatile uint32_t *) (SYSTICK + 0x4)
#define SYSTICK_VAL   (volatile uint32_t *) (SYSTICK + 0x8)

/* for SYSTICK_CTRL bit configuration */
#define COUNTFLAG_FINISH (1<<16)
#define ENABLE           (1<<0)

#define GPIO_MODER    (uint32_t *) GPIOD_MODER
#define GPIO_OTYPER   (uint32_t *) GPIOD_OTYPER
#define GPIO_OSPEEDR  (uint32_t *) GPIOD_OSPEEDR

/* port D ODR:
 * b31..b16 reserved,
 * b15..b0 usable:
        lower bits: b7..b0 bargraph display */
#define BARGRAPH_OUT  *(uint8_t *) GPIOD_ODR
#define SIMULATOR 1

void app_init(void);
void delay_250ns(void);
void delay_micro(uint32_t);
void delay_milli(uint32_t);

int main(void)
{
    app_init();
    while(1){
        BARGRAPH_OUT = 0;
        delay_milli(500);
        BARGRAPH_OUT = 0xff;
        delay_milli(500);
    }
    return 0;
}

void app_init(void)
{
    /* configure all I/O-s as output */
    *GPIO_MODER = 0x55555555;
    /* configure all outputs as push-pull (reset state) */
    *GPIO_OTYPER = 0;
    /* low speed on all GPIOs (reset state for port D)*/
    *GPIO_OSPEEDR = 0;
    BARGRAPH_OUT = 0xff;
}

/* STM32 PM0214 Rev 10 Page 250:
    1. Program reload value.
    2. Clear current value.
    3. Program Control and Status register. */
void delay_250ns(void)
{
    *SYSTICK_LOAD = 0x29;
    *SYSTICK_VAL = 0;
    *SYSTICK_CTRL = 5;
    while((*SYSTICK_CTRL & (1<<16)) == 0){
        __asm__("nop");
    };
}

void delay_micro(uint32_t us)
{
#if SIMULATOR
    us = us/1000;
    us++;
#endif
    for(uint32_t i=0; i < us; i++)                                              
        for(uint8_t j=0; j < 4; j++)                                            
            delay_250ns();

  }

void delay_milli(uint32_t ms)
{
    for(uint32_t i=0; i < ms; i++)
        delay_micro(1000);
}
