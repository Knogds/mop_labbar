#ifndef INTERRUPT_H
#define INTERRUPT_H

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

#define PERIPH                          0x40000000
#define BUS_APB2                 (PERIPH + 0x10000)
#define EXTI                    (BUS_APB2 + 0x3c00)
#define EXTI_IMR      (unsigned int *)(EXTI +  0x0)
#define EXTI_EMR      (unsigned int *)(EXTI +  0x4)
#define EXTI_RTSR     (unsigned int *)(EXTI +  0x8)
#define EXTI_FTSR     (unsigned int *)(EXTI +  0xc)
#define EXTI_SWIER    (unsigned int *)(EXTI + 0x10)
#define EXTI_PR       (unsigned int *)(EXTI + 0x14)

#define NVIC_ISER0     (unsigned int *) 0xe000e100
#define SCB_VTOR       (unsigned int *) 0xe000ed08
#define VECTOR_TABLE_BASE               0x2001c000
#define SYSTICK_HANDLER  (VECTOR_TABLE_BASE + 0x3c)
#define EXTI3_HANDLER    (VECTOR_TABLE_BASE + 0x64)

#endif