#include <stdint.h>

#define A 10
#define B 11
#define C 12
#define D 13
#define STAR 14
#define HASH 15

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

#define GPIO_MODER    (uint32_t *) GPIOD_MODER
#define GPIO_OTYPER   (uint32_t *) GPIOD_OTYPER
#define GPIO_PUPDR    (uint32_t *) GPIOD_PUPDR
#define GPIO_OSPEEDR  (uint32_t *) GPIOD_OSPEEDR

/* port D ODR:
 * b31..b16 reserved,
 * b15..b0 usable:
        upper bits: b7..b4 row output
        lower bits: b7..b0 seg display */
#define ROW_OUT       (uint8_t *) (GPIOD_ODR+1)
#define SEG_OUT       (uint8_t *)  GPIOD_ODR

/* port D IDR:
 * b31..b16 reserved,
 * b15..b0 usable:
        upper bits: b3..b0 row input */
#define ROW_IN        (uint8_t *) (GPIOD_IDR+1)

void app_init(void);
uint8_t keyb(void);
void kbdActivate(uint8_t);
uint8_t kbdGetCol(void);
void out7seg(uint8_t);
void pause(uint32_t ticks){while(ticks--){}}

int main(void)
{
    app_init();
    while(1){
        out7seg(keyb());
    }
    return 0;
}

void app_init(void)
{
    /* b11..b8 are inputs, the rest outputs */
    *GPIO_MODER = 0x55005555;
    /* configure all outputs as push-pull (reset state) */
    *GPIO_OTYPER = 0;
    /* configure inputs as pull-down */
    *GPIO_PUPDR = 0x00aa0000;
    /* low speed on all GPIOs (reset state for port D)*/
    *GPIO_OSPEEDR = 0;
    *SEG_OUT = 0;
}

uint8_t keyb(void)
{
    uint8_t key[]={   1, 2, 3,    A,
                      4, 5, 6,    B,
                      7, 8, 9,    C,
                   STAR, 0, HASH, D};
    int row, col;
    for(row = 1; row <= 4; row++){
        kbdActivate(row);
        if((col = kbdGetCol())){
            kbdActivate(0);
            return key[4*(row-1)+(col-1)];
        }
    }
    kbdActivate(0);
    return 0xff;
}

void kbdActivate(uint8_t row)
{
    *ROW_OUT = (1 << row + 3) & 0xf0;
}

uint8_t kbdGetCol(void)
{
    switch (*ROW_IN){
        case 1 : return 1; break;
        case 2 : return 2; break;
        case 4 : return 3; break;
        case 8 : return 4; break;
    }
}

void out7seg(uint8_t n)
{
    uint8_t character[] = {
        0x3f, 0x06, 0x5b, 0x4f,
        0x66, 0x6d, 0x7d, 0x07,
        0x7f, 0x6f, 0x77, 0x7c,
        0x39, 0x5e, 0x79, 0x71};
    *SEG_OUT = character[n];
}
