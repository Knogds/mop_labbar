#ifndef FLIPFLOP_IRQ__ACK_H
#define FLIPFLOP_IRQ_ACK_H

#define VECTOR_TABLE_BASE 0x2001c000

static void init_app(void);
static void exti3_irq_handler(void);
static void rst_hw_irq(unsigned int);

#endif