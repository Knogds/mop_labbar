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

#define PERIPH                             0x40000000
#define BUS_APB2                    (PERIPH + 0x10000)
#define SYSCFG                     (BUS_APB2 + 0x3800)
#define SYSCFG_MEMRMP  (unsigned int *)(SYSCFG +  0x0)
#define SYSCFG_PMC     (unsigned int *)(SYSCFG +  0x4)
#define SYSCFG_EXTICR1 (unsigned int *)(SYSCFG +  0x8)
#define SYSCFG_EXTICR2 (unsigned int *)(SYSCFG +  0xC)
#define SYSCFG_EXTICR3 (unsigned int *)(SYSCFG + 0x10)
#define SYSCFG_EXTICR4 (unsigned int *)(SYSCFG + 0x14)
#define SYSCFG_CMPCR   (unsigned int *)(SYSCFG + 0x20)

#endif