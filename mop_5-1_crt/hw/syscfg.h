#ifndef SYSCFG_H
#define SYSCFG_H

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

#define PERIPH                                      0x40000000
#define BUS_APB2                             (PERIPH + 0x10000)
#define SYSCFG                              (BUS_APB2 + 0x3800)
#define SYSCFG_MEMRMP  (volatile unsigned int *)(SYSCFG +  0x0)
#define SYSCFG_PMC     (volatile unsigned int *)(SYSCFG +  0x4)
#define SYSCFG_EXTICR1 (volatile unsigned int *)(SYSCFG +  0x8)
#define SYSCFG_EXTICR2 (volatile unsigned int *)(SYSCFG +  0xC)
#define SYSCFG_EXTICR3 (volatile unsigned int *)(SYSCFG + 0x10)
#define SYSCFG_EXTICR4 (volatile unsigned int *)(SYSCFG + 0x14)
#define SYSCFG_CMPCR   (volatile unsigned int *)(SYSCFG + 0x20)

/* SYSCFG external interrupt configuration register
(SYSCFG_EXTICRx) bit values */

/* With SYSCFG_EXTICR1 */
#define EXTI0(port)  (port<<0) 
#define EXTI1(port)  (port<<4) 
#define EXTI2(port)  (port<<8) 
#define EXTI3(port)  (port<<12)

/* With SYSCFG_EXTICR2 */
#define EXTI4(port)  (port<<0) 
#define EXTI5(port)  (port<<4) 
#define EXTI6(port)  (port<<8) 
#define EXTI7(port)  (port<<12)

/* With SYSCFG_EXTICR3 */
#define EXTI8(port)  (port<<0) 
#define EXTI9(port)  (port<<4) 
#define EXTI10(port) (port<<8) 
#define EXTI11(port) (port<<12)

/* With SYSCFG_EXTICR4 */
#define EXTI12(port) (port<<0) 
#define EXTI13(port) (port<<4) 
#define EXTI14(port) (port<<8) 
#define EXTI15(port) (port<<12)

#define EXTI_MASK_ALL 0xf
#define EXTIPORTA 0x0
#define EXTIPORTB 0x1
#define EXTIPORTC 0x2
#define EXTIPORTD 0x3
#define EXTIPORTE 0x4
#define EXTIPORTF 0x5
#define EXTIPORTG 0x6
#define EXTIPORTH 0x7
#define EXTIPORTI 0x8
#define EXTIPORTJ 0x9
#define EXTIPORTK 0xa

#endif