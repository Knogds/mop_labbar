#ifndef MOVEPONG_H
#define MOVEPONG_H

#include "draw.h"

#define A 10
#define B 11
#define C 12
#define D 13
#define STAR 14
#define HASH 15
#define CLEAR 1
#define DRAW 0

#define PERIPH                  0x40000000
#define AHB1          (PERIPH +    0x20000)
#define GPIOD         (AHB1   +      0xC00)
#define GPIOD_MODER   (GPIOD  +        0x0)
#define GPIOD_OTYPER  (GPIOD  +        0x4)
#define GPIOD_OSPEEDR (GPIOD  +        0x8)
#define GPIOD_PUPDR   (GPIOD  +        0xC)
#define GPIOD_IDR     (GPIOD  +       0x10)
#define GPIOD_ODR     (GPIOD  +       0x14)
#define GPIO_MODER    (unsigned int *)   GPIOD_MODER
#define GPIO_OTYPER   (unsigned int *)   GPIOD_OTYPER
#define GPIO_PUPDR    (unsigned int *)   GPIOD_PUPDR
#define GPIO_OSPEEDR  (unsigned int *)   GPIOD_OSPEEDR
#define ROW_OUT       (unsigned char *) (GPIOD_ODR+1)
#define COL_IN        (volatile unsigned char *) (GPIOD_IDR+1)
#define MAX_POINTS 30

typedef struct {
    int numpoints;
    int sizex;
    int sizey;
    point px[MAX_POINTS];
} geometry, *pgeometry;

typedef struct t_obj {
    pgeometry geom;
    int dirx, diry;
    int posx, posy;
    void (*draw) (struct t_obj *);
    void (*clear) (struct t_obj *);
    void (*move) (struct t_obj *);
    void (*set_speed) (struct t_obj *, int, int);
} object, *pobject;

char kbdGetCol(void);
char keyb(void);
geometry ball_geometry;
int overlaps(pobject, pobject);
int outside(pobject);
int random_gen(void);
static object ball;
static object creature;
void clear_object(pobject);
void draw_object(pobject);
void draw_object_gen(pobject, int);
void kbdActivate(char row);
void move_ball(pobject);
void move_creature(pobject);
void set_speed(pobject, int, int);

#endif
