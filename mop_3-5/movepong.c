#include "delay.h"
#include "draw.h"
#include "font.h"
#include "movepong.h"

int main(void)
{
    int running = 1;
    char key;
    int ch_dir = 0;
    pobject b = &ball;
    pobject p = &paddle;
    
    init_app();
    graphic_initialize();
    graphic_clear_screen();
    draw_object(b);
    draw_object(p);

    while(1){
        
        new_game(b, p);
        
        while(running){
            
            /* use ch_dir to do it just once */
            if(overlaps(b, p) && ch_dir == 1){
                b->dirx *= -1;

                ch_dir = 0;
            } else
                ch_dir = 1;

            if(ball_outside(b))
                running = 0;

            p->move(p);
            b->move(b);
            
            p->set_speed(p, 0, 0);
            delay_milli(7);;
            
            key = keyb();
            
            if(key==3) p->set_speed(p, 0, -3);
            if(key==9) p->set_speed(p, 0, 3);
            
        }
        
        font_set_pos(40,23);
        xprintf("Game over");
        
        font_set_pos(5,34);
        xprintf("Press 6 to continue");
        
        while(keyb() != 6){
            __asm__("nop");
        }

        running = 1;
    }
    return 0;
}

void new_game(pobject b, pobject p)
{
    graphic_clear_screen();
    
    draw_hline(1);
    draw_vline(1);
    draw_hline(64);
    
    b->posx = 70;
    b->posy = 30;
    
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
    int ymin_out = (new_posy < 2);
    int ymax_out = (new_posy + o->geom->sizey > 64);
    int xmin_out = (new_posx < 2);

    clear_object(o);
    
    if(xmin_out){
        o->dirx *= -1;
    }
    
    if(ymax_out || ymin_out){
        o->diry *= -1;
    }
    
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
    
    int ovlp_x = ax1 >= bx0; 
    int ovlp_y = ay0 <= by1 && ay1 >= by0;
    
    return (ovlp_x && ovlp_y);
}

int ball_outside(pobject o)
{
    return (o->posx >= 128)?1:0;
}

move_paddle(pobject o)
{
    int new_posy = o->posy + o->diry;
    int ymin_out = (new_posy < 1);
    int ymax_out = (new_posy + o->geom->sizey > 64);

    if(!ymax_out && !ymin_out){
        clear_object(o);
        o->posy += o->diry;
        draw_object(o);
    }
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
                         
geometry paddle_geometry = {27, 5, 9,                           
       {{0,0},{0,1},{0,2},{0,3},{0,4},{1,0},{1,4},{2,0},{2,4},                          
        {3,0},{3,2},{3,4},{4,0},{4,2},{4,4},{5,0},{5,2},{5,4},
        {6,0},{6,4},{7,0},{7,4},{8,0},{8,1},{8,2},{8,3},{8,4}}      
        };

static object ball = {
    &ball_geometry,
    3, 1, /* direction */
    /* 1, 1, */
    90, 10, /* position */
    draw_object,
    clear_object,
    move_ball,
    set_speed
};

static object paddle = {
    &paddle_geometry,
    0, 0, /* direction */
    123, 28, /* position */
    draw_object,
    clear_object,
    move_paddle,
    set_speed
};

/* works just for keys 3, 6, 9 */
char keyb(void)
{
    for(int i=4; i<=6; i++){            
        *ROW_OUT = (1<<i);
        if(*COL_IN == 4){
            if(i==4) return 3;
            if(i==5) return 6;
            if(i==6) return 9;
        }
    }
    return 0;
}
