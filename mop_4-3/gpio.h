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

#define PERIPH                           0x40000000
#define AHB1          (PERIPH +             0x20000)

#define GPIOA         (AHB1 +                   0x0)
#define GPIOB         (AHB1 +                 0x400)
#define GPIOC         (AHB1 +                 0x800)
#define GPIOD         (AHB1 +                 0xC00)
#define GPIOE         (AHB1 +                0x1000)

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

#define GPIOD_MODER   (unsigned int *)(GPIOD +  0x0)
#define GPIOD_OTYPER  (unsigned int *)(GPIOD +  0x4)
#define GPIOD_OSPEEDR (unsigned int *)(GPIOD +  0x8)
#define GPIOD_PUPDR   (unsigned int *)(GPIOD +  0xC)
#define GPIOD_IDR     (volatile unsigned int *)(GPIOD + 0x10)
#define GPIOD_ODR     (unsigned int *)(GPIOD + 0x14)
#define GPIOD_BSRR    (unsigned int *)(GPIOD + 0x18)
#define GPIOD_LCKR    (unsigned int *)(GPIOD + 0x1C)
#define GPIOD_AFRL    (unsigned int *)(GPIOD + 0x20)
#define GPIOD_AFRH    (unsigned int *)(GPIOD + 0x24)

#define GPIOE_MODER   (unsigned int *)(GPIOE +  0x0)
#define GPIOE_OTYPER  (unsigned int *)(GPIOE +  0x4)
#define GPIOE_OSPEEDR (unsigned int *)(GPIOE +  0x8)
#define GPIOE_PUPDR   (unsigned int *)(GPIOE +  0xC)
#define GPIOE_IDR     (volatile unsigned int *)(GPIOE + 0x10)
#define GPIOE_ODR     (unsigned int *)(GPIOE + 0x14)
#define GPIOE_BSRR    (unsigned int *)(GPIOE + 0x18)
#define GPIOE_LCKR    (unsigned int *)(GPIOE + 0x1C)
#define GPIOE_AFRL    (unsigned int *)(GPIOE + 0x20)
#define GPIOE_AFRH    (unsigned int *)(GPIOE + 0x24)

#endif