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

#define PERIPH                                0x40000000
#define BUS_APB2                       (PERIPH + 0x10000)
#define EXTI                          (BUS_APB2 + 0x3c00)
#define EXTI_IMR   (volatile unsigned int *)(EXTI +  0x0)
#define EXTI_EMR   (volatile unsigned int *)(EXTI +  0x4)
#define EXTI_RTSR  (volatile unsigned int *)(EXTI +  0x8)
#define EXTI_FTSR  (volatile unsigned int *)(EXTI +  0xc)
#define EXTI_SWIER (volatile unsigned int *)(EXTI + 0x10)
#define EXTI_PR    (volatile unsigned int *)(EXTI + 0x14)

/* Private peripheral bus */
#define BUS_PPB                                  0xe0000000

#define SCB_VTOR (volatile unsigned int *)(BUS_PPB + 0xed08)

/* vector table offset from 0x00000000 for use with SCV_VTOR */
#ifndef VECTOR_TABLE_BASE
#define VECTOR_TABLE_BASE 0x00000000
#endif

/* ... */
#define SYSTICK_HANDLER (void (**)(void))(VECTOR_TABLE_BASE + 0x3c)
/* ... */ 
#define EXTI0_HANDLER   (void (**)(void))(VECTOR_TABLE_BASE + 0x58)
#define EXTI1_HANDLER   (void (**)(void))(VECTOR_TABLE_BASE + 0x5c)
#define EXTI2_HANDLER   (void (**)(void))(VECTOR_TABLE_BASE + 0x60)
#define EXTI3_HANDLER   (void (**)(void))(VECTOR_TABLE_BASE + 0x64)
#define EXTI4_HANDLER   (void (**)(void))(VECTOR_TABLE_BASE + 0x68)
/* ... */

/* x = 0 to 7 */
#define NVIC_ISER(x)  (volatile unsigned int *)(BUS_PPB + 0xe100 + (0x04 * x))
#define NVIC_ICER(x)  (volatile unsigned int *)(BUS_PPB + 0xe180 + (0x04 * x))
#define NVIC_ISPR(x)  (volatile unsigned int *)(BUS_PPB + 0xe200 + (0x04 * x))
#define NVIC_ICPR(x)  (volatile unsigned int *)(BUS_PPB + 0xe280 + (0x04 * x))
#define NVIC_IABR(x)  (volatile unsigned int *)(BUS_PPB + 0xe300 + (0x04 * x))

/* NVIC_ISER0 interrupts 0-31 ..add prefix? */
#define IRQ_WWDF                (1<<0)
#define IRQ_PVD                 (1<<1)
#define IRQ_TAMP_STAMP          (1<<2)
#define IRQ_RTC_WKUP            (1<<3)
#define IRQ_FLASH               (1<<4)
#define IRQ_RCC                 (1<<5)
#define IRQ_EXTI0 (1<<6)
#define IRQ_EXTI1 (1<<7)
#define IRQ_EXTI2 (1<<8)
#define IRQ_EXTI3               (1<<9)
#define IRQ_EXTI4              (1<<10)
#define IRQ_DMA1_Stream0       (1<<11)
#define IRQ_DMA1_Stream1       (1<<12)
#define IRQ_DMA1_Stream2       (1<<13)
#define IRQ_DMA1_Stream3       (1<<14)
#define IRQ_DMA1_Stream4       (1<<15)
#define IRQ_DMA1_Stream5       (1<<16)
#define IRQ_DMA1_Stream6       (1<<17)
#define IRQ_ADC                (1<<18)
#define IRQ_CAN1_TX            (1<<19)
#define IRQ_CAN1_RX0           (1<<20)
#define IRQ_CAN1_RX1           (1<<21)
#define IRQ_CAN1_SCE           (1<<22)
#define IRQ_EXTI9_5            (1<<23)
#define IRQ_TIM1_BRK_TIM9      (1<<24)
#define IRQ_TIM1_UP_TIM10      (1<<25)
#define IRQ_TIM1_TRG_COM_TIM11 (1<<26)
#define IRQ_TIM1_CC            (1<<27)
#define IRQ_TIM2               (1<<28)
#define IRQ_TIM3               (1<<29)
#define IRQ_TIM4               (1<<30)
#define IRQ_I2C1_EV            (1<<31)

#endif

/*
 * TODO
 * 
 0  WWDF                0x00000040
 1  PVD                 0x00000044
 2  TAMP_STAMP          0x00000048
 3  RTC_WKUP            0x0000004C
 4  FLASH               0x00000050
 5  RCC                 0x00000054
 6  EXTI0               0x00000058
 7  EXTI1               0x0000005C
 8  EXTI2               0x00000060
 9  EXTI3               0x00000064
10  EXTI4               0x00000068
11  DMA1_Stream0        0x0000006C
12  DMA1_Stream1        0x00000070
13  DMA1_Stream2        0x00000074
14  DMA1_Stream3        0x00000078
15  DMA1_Stream4        0x0000007C
16  DMA1_Stream5        0x00000080
17  DMA1_Stream6        0x00000084
18  ADC                 0x00000088
19  CAN1_TX             0x0000008C
20  CAN1_RX0            0x00000090
21  CAN1_RX1            0x00000094
22  CAN1_SCE            0x00000098
23  EXTI9_5             0x0000009C
24  TIM1_BRK_TIM9       0x000000A0
25  TIM1_UP_TIM10       0x000000A4
26  TIM1_TRG_COM_TIM11  0x000000A8
27  TIM1_CC             0x000000AC
28  TIM2                0x000000B0
29  TIM3                0x000000B4
30  TIM4                0x000000B8
31  I2C1_EV             0x000000BC
32  I2C1_ER             0x000000C0
33  I2C2_EV             0x000000C4
34  I2C2_ER             0x000000C8
35  SPI1                0x000000CC
36  SPI2                0x000000D0
37  USART1              0x000000D4
38  USART2              0x000000D8
39  USART3              0x000000DC
40  EXTI15_10           0x000000E0
41  RTC_Alarm           0x000000E4
42  OTG_FS_WKUP         0x000000E8
43  TIM8_BRK_TIM12      0x000000EC
44  TIM8_UP_TIM13       0x000000F0
45  TIM8_TRG_COM_TIM14  0x000000F4
46  TIM8_CC             0x000000F8
47  DMA1_Stream7        0x000000FC
48  FSMC                0x00000100
49  SDIO                0x00000104
50  TIM5                0x00000108
51  SPI3                0x0000010C
52  UART4               0x00000110
53  UART5               0x00000114
54  TIM6_DAC            0x00000118
55  TIM7                0x0000011C
56  DMA2_Stream0        0x00000120
57  DMA2_Stream1        0x00000124
58  DMA2_Stream2        0x00000128
59  DMA2_Stream3        0x0000012C
60  DMA2_Stream4        0x00000130
61  ETH                 0x00000134
62  ETH_WKUP            0x00000138
63  CAN2_TX             0x0000013C
64  CAN2_RX0            0x00000140
65  CAN2_RX1            0x00000144
66  CAN2_SCE            0x00000148
67  OTG_FS              0x0000014C
68  DMA2_Stream5        0x00000150
69  DMA2_Stream6        0x00000154
70  DMA2_Stream7        0x00000158
71  USART6              0x0000015C
72  I2C3_EV             0x00000160
73  I2C3_ER             0x00000164
74  OTG_HS_EP0_OUT      0x00000168
75  OTG_HS_EP1_IN       0x0000016C
76  OTG_HS_WKUP         0x00000170
77  OTG_HS              0x00000174
78  DCMI                0x00000178
79  CRYP                0x0000017C
80  HASH_RNG            0x00000180
81  FPU                 0x00000184
*/

