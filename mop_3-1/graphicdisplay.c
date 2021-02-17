#include "delay.h"
#include "draw.h"
#include "font.h"

int main(void)
{
    line lines[] = {
        {40, 10, 100, 10},
        {40, 10, 100, 20},
        {40, 10, 100, 30},
        {40, 10, 100, 40},
        {40, 10, 100, 50},
        {40, 10, 100, 60},
        {40, 10, 100, 60},
        {40, 10, 90, 60},
        {40, 10, 80, 60},
        {40, 10, 70, 60},
        {40, 10, 60, 60},
        {40, 10, 50, 60},
        {40, 10, 40, 60}
    };
    
    rect rectangles[] = {
        {10, 10, 20, 10},
        {25, 25, 10, 20},
        {40, 30, 70, 20},
        {60, 35, 10, 10},
        {70, 10, 5, 5}
    };

    polypoint pg8 = {20, 20, 0};
    polypoint pg7 = {20, 55, &pg8};
    polypoint pg6 = {70, 60, &pg7};
    polypoint pg5 = {80, 35, &pg6};
    polypoint pg4 = {100, 25, &pg5};
    polypoint pg3 = {90, 10, &pg4};
    polypoint pg2 = {40, 10, &pg3};
    polypoint pg1 = {20, 20, &pg2};

    graphic_initialize();
    graphic_clear_screen();
    
    while(1){

        /* draw lines */
        
        for(int i=0; i<sizeof(lines)/sizeof(line);i++){
            pline l = &lines[i];
            font_set_pos(1,10);
            xprintf("x0:%03d\nx1:%03d\ny0:%03d\ny1:%03d",
                    l->xy0.x, l->xy1.x, l->xy0.y, l->xy1.y);
            draw_line(l);
            delay_milli(500);
        }

        graphic_clear_screen();   

        /* draw rectangles */
        
        for(int i=0; i<sizeof(rectangles)/sizeof(rect);i++){
            prect r = &rectangles[i];
            font_set_pos(1,56);
            xprintf("x:%02d y:%02d w:%02d h:%02d",
            r->origo.x, r->origo.y, r->width, r->height);
            draw_rect(r);
            delay_milli(500);
        }
        
        graphic_clear_screen();
        
        /* draw a polygon */
        draw_polygon(&pg1);
        delay_milli(1000);
        
        graphic_clear_screen();

    }
    
    return 0;
}