#ifndef GPIO_H
#define GPIO_H

/*
   Hw adresses, names, usage description used in this file are partly or
   completely extracted from

   RM0090 Reference manual
   STM32F405/415, STM32F407/417, STM32F427/437 and
   STM32F429/439 advanced Arm®-based 32-bit MCUs

   or

   PM0214 Programming manual
   STM32 Cortex®-M4 MCUs and MPUs programming manual

   both owned by STMicroelectronics
*/

#define PERIPH      0x40000000
#define AHB1 (PERIPH + 0x20000)

#define GPIOA (AHB1 +      0x0)
#define GPIOB (AHB1 +    0x400)
#define GPIOC (AHB1 +    0x800)
#define GPIOD (AHB1 +    0xC00)
#define GPIOE (AHB1 +   0x1000)

#define GPIO0   (1<<0)
#define GPIO1   (1<<1)
#define GPIO2   (1<<2)
#define GPIO3   (1<<3)
#define GPIO4   (1<<4)
#define GPIO5   (1<<5)
#define GPIO6   (1<<6)
#define GPIO7   (1<<7)
#define GPIO8   (1<<8)
#define GPIO9   (1<<9)
#define GPIO10 (1<<10)
#define GPIO11 (1<<11)
#define GPIO12 (1<<12)
#define GPIO13 (1<<13)
#define GPIO14 (1<<14)
#define GPIO15 (1<<15)

/*

GPIOx_MODER
00: Input (reset state)
01: General purpose output mode
10: Alternate function mode
11: Analog mode

GPIOx_OTYPER
0: Output push-pull (reset state)
1: Output open-drain

GPIOx_OSPEEDR
00: Low speed
01: Medium speed
10: High speed
11: Very high speed

GPIOx_PUPDR
00: No pull-up, pull-down
01: Pull-up
10: Pull-down
11: Reserved

*/

#define GPIOA_MODER   (volatile unsigned int *)(GPIOA +  0x0)
#define GPIOA_OTYPER  (volatile unsigned int *)(GPIOA +  0x4)
#define GPIOA_OSPEEDR (volatile unsigned int *)(GPIOA +  0x8)
#define GPIOA_PUPDR   (volatile unsigned int *)(GPIOA +  0xC)
#define GPIOA_IDR     (volatile unsigned int *)(GPIOA + 0x10)
#define GPIOA_ODR     (volatile unsigned int *)(GPIOA + 0x14)
#define GPIOA_BSRR    (volatile unsigned int *)(GPIOA + 0x18)
#define GPIOA_LCKR    (volatile unsigned int *)(GPIOA + 0x1C)
#define GPIOA_AFRL    (volatile unsigned int *)(GPIOA + 0x20)
#define GPIOA_AFRH    (volatile unsigned int *)(GPIOA + 0x24)

#define GPIOB_MODER   (volatile unsigned int *)(GPIOB +  0x0)
#define GPIOB_OTYPER  (volatile unsigned int *)(GPIOB +  0x4)
#define GPIOB_OSPEEDR (volatile unsigned int *)(GPIOB +  0x8)
#define GPIOB_PUPDR   (volatile unsigned int *)(GPIOB +  0xC)
#define GPIOB_IDR     (volatile unsigned int *)(GPIOB + 0x10)
#define GPIOB_ODR     (volatile unsigned int *)(GPIOB + 0x14)
#define GPIOB_BSRR    (volatile unsigned int *)(GPIOB + 0x18)
#define GPIOB_LCKR    (volatile unsigned int *)(GPIOB + 0x1C)
#define GPIOB_AFRL    (volatile unsigned int *)(GPIOB + 0x20)
#define GPIOB_AFRH    (volatile unsigned int *)(GPIOB + 0x24)

#define GPIOC_MODER   (volatile unsigned int *)(GPIOC +  0x0)
#define GPIOC_OTYPER  (volatile unsigned int *)(GPIOC +  0x4)
#define GPIOC_OSPEEDR (volatile unsigned int *)(GPIOC +  0x8)
#define GPIOC_PUPDR   (volatile unsigned int *)(GPIOC +  0xC)
#define GPIOC_IDR     (volatile unsigned int *)(GPIOC + 0x10)
#define GPIOC_ODR     (volatile unsigned int *)(GPIOC + 0x14)
#define GPIOC_BSRR    (volatile unsigned int *)(GPIOC + 0x18)
#define GPIOC_LCKR    (volatile unsigned int *)(GPIOC + 0x1C)
#define GPIOC_AFRL    (volatile unsigned int *)(GPIOC + 0x20)
#define GPIOC_AFRH    (volatile unsigned int *)(GPIOC + 0x24)

#define GPIOD_MODER   (volatile unsigned int *)(GPIOD +  0x0)
#define GPIOD_OTYPER  (volatile unsigned int *)(GPIOD +  0x4)
#define GPIOD_OSPEEDR (volatile unsigned int *)(GPIOD +  0x8)
#define GPIOD_PUPDR   (volatile unsigned int *)(GPIOD +  0xC)
#define GPIOD_IDR     (volatile unsigned int *)(GPIOD + 0x10)
#define GPIOD_ODR     (volatile unsigned int *)(GPIOD + 0x14)
#define GPIOD_BSRR    (volatile unsigned int *)(GPIOD + 0x18)
#define GPIOD_LCKR    (volatile unsigned int *)(GPIOD + 0x1C)
#define GPIOD_AFRL    (volatile unsigned int *)(GPIOD + 0x20)
#define GPIOD_AFRH    (volatile unsigned int *)(GPIOD + 0x24)

#define GPIOE_MODER   (volatile unsigned int *)(GPIOE +  0x0)
#define GPIOE_OTYPER  (volatile unsigned int *)(GPIOE +  0x4)
#define GPIOE_OSPEEDR (volatile unsigned int *)(GPIOE +  0x8)
#define GPIOE_PUPDR   (volatile unsigned int *)(GPIOE +  0xC)
#define GPIOE_IDR     (volatile unsigned int *)(GPIOE + 0x10)
#define GPIOE_ODR     (volatile unsigned int *)(GPIOE + 0x14)
#define GPIOE_BSRR    (volatile unsigned int *)(GPIOE + 0x18)
#define GPIOE_LCKR    (volatile unsigned int *)(GPIOE + 0x1C)
#define GPIOE_AFRL    (volatile unsigned int *)(GPIOE + 0x20)
#define GPIOE_AFRH    (volatile unsigned int *)(GPIOE + 0x24)

#endif