#ifndef SYSTICK_H
#define SYSTICK_H

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

#define STK                                     0xe000e010
#define STK_CTRL      (volatile unsigned int *) (STK + 0x0)
#define STK_LOAD      (volatile unsigned int *) (STK + 0x4)
#define STK_VAL       (volatile unsigned int *) (STK + 0x8)

#endif