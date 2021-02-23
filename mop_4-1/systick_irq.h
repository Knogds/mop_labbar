#ifndef SYSTICK_IRQ_H
#define SYSTICK_IRQ_H

#define SIMULATOR

#ifdef  SIMULATOR
#define DELAY_COUNT 100
#else
#define DELAY_COUNT 1000000
#endif

#define PERIPH                  0x40000000
#define AHB1          (PERIPH +    0x20000)
#define GPIOD         (AHB1   +      0xC00)
#define GPIOD_MODER   (GPIOD  +        0x0)
#define GPIOD_OTYPER  (GPIOD  +        0x4)
#define GPIOD_OSPEEDR (GPIOD  +        0x8)
#define GPIOD_PUPDR   (GPIOD  +        0xC)
#define GPIOD_IDR     (GPIOD  +       0x10)
#define GPIOD_ODR     (GPIOD  +       0x14)
#define GPIOD_BSRR    (GPIOD  +       0x18)
#define GPIOD_LCKR    (GPIOD  +       0x1C)
#define GPIOD_AFRL    (GPIOD  +       0x20)
#define GPIOD_AFRH    (GPIOD  +       0x24)

#define GPIO_MODER    (unsigned int *) GPIOD_MODER
#define GPIO_OTYPER   (unsigned int *) GPIOD_OTYPER
#define GPIO_PUPDR    (unsigned int *) GPIOD_PUPDR
#define GPIO_OSPEEDR  (unsigned int *) GPIOD_OSPEEDR
#define GPIO_ODR      (unsigned int *) GPIOD_ODR
#define GPIO_ODR_LOW  (unsigned char *) GPIOD_ODR
#define GPIO_ODR_HIGH (unsigned char *) (GPIOD_ODR+1)

#define STK                                 0xe000e010
#define STK_CTRL  (volatile unsigned int *) (STK + 0x0)
#define STK_LOAD  (volatile unsigned int *) (STK + 0x4)
#define STK_VAL   (volatile unsigned int *) (STK + 0x8)

#define RELOAD_VALUE (0xa8-1)

/* for STK_CTRL bit configuration */
#define COUNTFLAG       (1<<16)
#define ENABLE           (1<<0)
#define TICKINT          (1<<1)
#define SOURCE_CLK       (1<<2)

#define SCB_VTOR (unsigned int *) 0xe000ed08
#define VECTOR_TABLE_BASE         0x2001c000
#define SYSTICK_HANDLER (VECTOR_TABLE_BASE + 0x3c)

void delay(unsigned int);
void delay_1mikro(void);
void systick_irq_handler(void);

#endif