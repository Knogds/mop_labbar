#include <stdint.h>

#define PERIPH                  0x40000000
#define AHB1          (PERIPH +    0x20000)
#define GPIOE         (AHB1   +     0x1000)
#define GPIOE_MODER   (GPIOE  +        0x0)
#define GPIOE_OTYPER  (GPIOE  +        0x4)
#define GPIOE_OSPEEDR (GPIOE  +        0x8)
#define GPIOE_PUPDR   (GPIOE  +        0xC)
#define GPIOE_IDR     (GPIOE  +       0x10)
#define GPIOE_ODR     (GPIOE  +       0x14)
#define GPIO_MODER    (uint32_t *) GPIOE_MODER
#define GPIO_OTYPER   (uint32_t *) GPIOE_OTYPER
#define GPIO_OSPEEDR  (uint32_t *) GPIOE_OSPEEDR
#define GPIO_PUPDR    (uint32_t *) GPIOE_PUPDR
/* high bits, data on LCD */
#define DATA_ODR      (uint8_t *) (GPIOE_ODR+1)
#define DATA_IDR      (volatile uint8_t *) (GPIOE_IDR+1)
/* low bits, command bits on LCD */
#define COMMAND_ODR   (uint8_t *)  GPIOE_ODR

#define SYSTICK                                 0xE000E010
#define SYSTICK_CTRL  (volatile uint32_t *) (SYSTICK + 0x0)
#define SYSTICK_LOAD  (volatile uint32_t *) (SYSTICK + 0x4)
#define SYSTICK_VAL   (volatile uint32_t *) (SYSTICK + 0x8)

#define UP      1
#define DOWN    0
#define E       6
#define SELECT  2
#define RW      1
#define RS      0
#define OPT_ONE_ROW 0
#define OPT_TWO_ROWS 1
#define OPT_5X8 0
#define OPT_5x11 1
#define OPT_BLINKING_OFF 0
#define OPT_BLINKING_ON 1
#define OPT_DISPLAY_OFF 0
#define OPT_DISPLAY_ON 1
#define OPT_CURSOR_OFF 0
#define OPT_CURSOR_ON 1
#define OPT_CURSOR_BLINKING_OFF 0
#define OPT_CURSOR_BLINKING_ON 1
#define OPT_RTL_MODE 0
#define OPT_LTR_MODE 1
#define OPT_SHIFT_OFF 0
#define OPT_SHIFT_ON 1
#define OPT_CLEAR_LCD 1
#define SIMULATOR 1

uint8_t ascii_read_controller(void);
uint8_t ascii_read_data(void);
uint8_t ascii_read_status(void);
void app_init(void);
void ascii_clear_display(void);
void ascii_ctrl_bit_clear(uint8_t);
void ascii_ctrl_bit_set(uint8_t);
void ascii_init(void);
void ascii_print(uint8_t, uint8_t, uint8_t **);
void ascii_write_cmd(uint8_t);
void ascii_write_controller(uint8_t);
void ascii_write_data(uint8_t);
void delay_250ns(void);
void delay_micro(uint32_t);
void delay_milli(uint32_t);



int main(void)
{
    app_init();
    ascii_init();

    ascii_print(5, 1, "DATAVETARE");
    ascii_print(7, 2, "RULEZ");
}

void ascii_print(uint8_t x, uint8_t y, uint8_t **msg)
{
    uint8_t *s = msg;
    ascii_gotoxy(x,y);
    while (*s)
        ascii_write_char(*s++);
}

void app_init(void)
{
    /* configure all I/O-s as output */
    *GPIO_MODER = 0x55555555;
    *GPIO_OTYPER = 0;
	/* all inputs pull-down */
    *GPIO_PUPDR = 0xaaaa0000;
    /* very high speed on all GPIOs */
    *GPIO_OSPEEDR = 0xffffffff;
}


void delay_systick(uint32_t load)
{
    *SYSTICK_LOAD = load;
    *SYSTICK_VAL = 0;
    *SYSTICK_CTRL = 5;
    while((*SYSTICK_CTRL & (1<<16)) == 0){
        __asm__("nop");
    };
}

void ascii_ctrl_bit_set(uint8_t x)
{
    *COMMAND_ODR |= (1 << SELECT)|(1 << x);
}

void ascii_ctrl_bit_clear(uint8_t x)
{
    *COMMAND_ODR &= ~(1 << x);
    *COMMAND_ODR |= (1 << SELECT);
}

void ascii_write_controller(uint8_t byte)
{
    /* delay >40ns */
    delay_systick(0xee);
    ascii_ctrl_bit_set(E);
    *DATA_ODR = byte;
    ascii_ctrl_bit_clear(E);
    /* delay >10ns */
    delay_systick(0x3c);
}

uint8_t ascii_read_controller(void)
{
    uint8_t data;
    ascii_ctrl_bit_set(E);
    /* delay >360ns */
    delay_systick(0x85f);
    data = *DATA_IDR;
    ascii_ctrl_bit_clear(E);
    return data;
}

void ascii_write_cmd(uint8_t command)
{
    ascii_ctrl_bit_clear(RS);
    ascii_ctrl_bit_clear(RW);
    ascii_write_controller(command);
}

void ascii_write_data(uint8_t data)
{
    ascii_ctrl_bit_set(RS);
    ascii_ctrl_bit_clear(RW);
    ascii_write_controller(data);
}

uint8_t ascii_read_status(void)
{
    uint8_t data;
    *GPIO_MODER = 0x00005555;
    ascii_ctrl_bit_clear(RS);
    ascii_ctrl_bit_set(RW);
    data = ascii_read_controller();
    *GPIO_MODER = 0x55555555;
    delay_micro(43);
    return data;
}

uint8_t ascii_read_data(void)
{
    uint8_t data;
    *GPIO_MODER = 0x00005555;
    ascii_ctrl_bit_set(RS);
    ascii_ctrl_bit_set(RW);
    data = ascii_read_controller();
    *GPIO_MODER = 0x55555555;
    delay_micro(43);
    return data;
}

void ascii_write_char(uint8_t c)
{
    while(ascii_read_status() != 0){
        __asm__("nop");
    }
    delay_micro(8);
    ascii_write_data(c);
    delay_micro(43);
}

void ascii_gotoxy(uint8_t x, uint8_t y)
{
    if(y == 2)
        x += 0x40;
    /* adress command */
    ascii_write_cmd ((1 << 7) | x);
    delay_micro(39);
}

void ascii_clear_display(void)
{
    /* Or just 0x01 */
    ascii_write_cmd((OPT_CLEAR_LCD<<0));
    delay_milli(2);
}

void ascii_init(void)
{
    /* function set */
    ascii_write_cmd((3<<4) | (OPT_TWO_ROWS<<3)
                           | (OPT_5x11<<2));
    delay_micro(39);
    
    /* display control */
    ascii_write_cmd((1<<3) | (OPT_DISPLAY_ON<<2)
                           | (OPT_CURSOR_ON<<1)
                           | (OPT_CURSOR_BLINKING_OFF<<0));
    delay_micro(39);
    
    ascii_clear_display();
    
    /* entry mode set */
    ascii_write_cmd((1<<2) | (OPT_LTR_MODE<<1)
                           | (OPT_SHIFT_OFF<<0));
    delay_micro(39);
}

void delay_250ns(void)
{
    *SYSTICK_LOAD = 0x29;
    *SYSTICK_VAL = 0;
    *SYSTICK_CTRL = 5;
    while((*SYSTICK_CTRL & (1<<16)) == 0){
        __asm__("nop");
    }
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
