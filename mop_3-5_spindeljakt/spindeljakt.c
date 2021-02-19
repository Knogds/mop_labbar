#include "delay.h"
#include "draw.h"
#include "font.h"
#include "spindeljakt.h"

int main(void)
{
    int running = 1;
    int won = 0;
    char key = 0;
    pobject b = &ball;
    pobject p = &creature;
    
    init_app();
    graphic_initialize();
    graphic_clear_screen();

    draw_object(b);
    draw_object(p);

    while(1){
        
        new_game(b, p);
        
        while(running){
            
            if(overlaps(b, p)){
                running = 0;
                won = 1;
            }
                
            if(outside(p)){
                running = 0;
                won = 0;
            }

            if(running){
                p->move(p);
                b->move(b);
            }
            
            p->set_speed(p, 0, 0);
            
            delay_milli(8);
            
            key = keyb();
            
            if(key==6) p->set_speed(p, 2, 0);
            if(key==4) p->set_speed(p, -2, 0);
            if(key==2) p->set_speed(p, 0, -2);
            if(key==8) p->set_speed(p, 0, 2);
            
        }
        
        font_set_pos(40,20);
        if(won == 1)
            xprintf("Well done!");
        else
            xprintf("Game over");
        
        font_set_pos(5,34);
        xprintf("Press 5 to continue");
        
        while(keyb() != 5)
            __asm__("nop");

        running = 1;
        won = 0;
    }
    return 0;
}

void new_game(pobject b, pobject p)
{
    graphic_clear_screen();
    
    b->posx = 70;
    b->posy = 30;
    
    p->posx = 60;
    p->posy = 40;

}
void init_app(void)
{
    /* b11..b8 are inputs, the rest outputs */
    *GPIO_MODER = 0x55005555;
    /* configure all outputs as push-pull (reset state) */
    *GPIO_OTYPER = 0;
    /* configure inputs as pull-down */
    *GPIO_PUPDR = 0x00aa0000;
    /* low speed on all GPIOs (reset state for port D)*/
    *GPIO_OSPEEDR = 0;
}

void draw_object_gen(pobject o, int clear)
{
    char x, off_x;
    char y, off_y;
    off_x = o->posx;
    off_y = o->posy;
    point *px = o->geom->px;

    for(int i=0; i < o->geom->numpoints; i++){
        x = px[i].x;
        y = px[i].y;
        if(clear)
            graphic_pixel_clear(y+off_x, x+off_y);
        else
            graphic_pixel_set(y+off_x, x+off_y);
    }
}

void draw_object(pobject o)
{
    draw_object_gen(o, DRAW);
}

void clear_object(pobject o)
{
    draw_object_gen(o, CLEAR);
}

void move_ball(pobject o)
{
    int new_posy = o->posy + o->diry;
    int new_posx = o->posx + o->dirx;
    int ymin_out = (new_posy < 1);
    int ymax_out = (new_posy + o->geom->sizey > 64);
    int xmin_out = (new_posx < 1);
    int xmax_out = (new_posx + o->geom->sizey > 128);
    
    if(xmin_out || xmax_out){
        o->dirx *= -1;
    }
    
    if(ymax_out || ymin_out){
        o->diry *= -1;
    }

    clear_object(o);
    
    o->posx += o->dirx;
    o->posy += o->diry;
      
    draw_object(o);
}

int overlaps(pobject a, pobject b)
{
    int ax0 = a->posx;
    int ay0 = a->posy;
    int ax1 = a->posx + a->geom->sizex;
    int ay1 = a->posy + a->geom->sizey;
    int bx0 = b->posx;
    int by0 = b->posy;
    int bx1 = b->posx + b->geom->sizex;
    int by1 = b->posy + b->geom->sizey;
    
    int ovlp_x = ax0 <= bx1 && ax1 >= bx0;
    int ovlp_y = ay0 <= by1 && ay1 >= by0;
    
    return (ovlp_x && ovlp_y);
}

int outside(pobject o)
{
    int new_posx = o->posx + o->dirx;
    int new_posy = o->posy + o->diry;
    int ymin_out = (new_posy < 1);
    int ymax_out = (new_posy + o->geom->sizey > 64);
    int xmin_out = (new_posx < 1);
    int xmax_out = (new_posx + o->geom->sizex > 128);

    if(ymax_out || ymin_out || xmax_out || xmin_out){
        return 1;
    }
    return 0;
}

move_creature(pobject o)
{
    clear_object(o);
    o->posx += o->dirx;
    o->posy += o->diry;
    draw_object(o);
}

void set_speed(pobject o, int x, int y)
{
    o->dirx = x;
    o->diry = y;
}

geometry ball_geometry = {12,  /* numpoints */
                          4,4, /* sizex, sizey */
                          {{0,1},{0,2},{1,0},{1,1},
                           {1,2},{1,3},{2,0},{2,1},
                           {2,2},{2,3},{3,1},{3,2}}
};
                         
geometry creature_geometry = {22, 5, 7,
                           {{0,2},{0,3},{1,1},{1,4},
                            {2,0},{2,1},{2,2},{2,3},
                            {2,4},{2,5},{3,0},{3,2},
                            {3,3},{3,5},{4,1},{4,4},
                            {5,2},{5,3},{6,1},{6,4},
                            {7,0},{7,5}}
};

static object ball = {
    &ball_geometry,
    4, 1, /* direction */
    70, 30, /* position */
    draw_object,
    clear_object,
    move_ball,
    set_speed
};

static object creature = {
    &creature_geometry,
    0, 0, /* direction */
    60, 40, /* position */
    draw_object,
    clear_object,
    move_creature,
    set_speed
};



/*
ROW_OUT: b4----1  2  3  A
         b5----4  5  6  B
         b6----7  8  9  C
         b7----*  0  #  D
               |  |  |  |
              b0 b1 b2 b3
COL_IN value:  1  2  4  8
*/
 
/* use only the keys we need */
char keyb(void)
{
    *ROW_OUT = (1<<4);
    if(*COL_IN == 2) return 2;
    *ROW_OUT = (1<<5);
    if(*COL_IN == 1) return 4;
    if(*COL_IN == 2) return 5;
    if(*COL_IN == 4) return 6;
    *ROW_OUT = (1<<6);
    if(*COL_IN == 2) return 8;
    return 0;
}
