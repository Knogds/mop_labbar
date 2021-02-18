#include "draw.h"

void draw_line(pline l)
{
    char x0 = l->xy0.x;
    char y0 = l->xy0.y;
    char x1 = l->xy1.x;
    char y1 = l->xy1.y;
    
    draw_line_xy(x0, x1, y0, y1);
}

void draw_rect(prect r)
{
    char x0 = r->origo.x;
    char y0 = r->origo.y;
    char width = r->width;
    char height = r->height;
    
    draw_line_xy(x0, x0+width, y0, y0);
    draw_line_xy(x0+width, x0+width, y0, y0+height);
    draw_line_xy(x0, x0+width, y0+height, y0+height);
    draw_line_xy(x0, x0, y0, y0+height);
}

int draw_polygon(ppolypoint pp)
{
    while(pp->next != 0){
        draw_line_xy(pp->xy.x, pp->next->xy.x, pp->xy.y, pp->next->xy.y);
        pp = pp->next;
    }
    return 0;
}

void draw_hline(char y)
{
    for(char i=1; i<127; i++){
        graphic_pixel_set(i, y);
    }
}

void draw_vline(char x)
{
    for(char i=1; i<64; i++){
        graphic_pixel_set(x, i);
    }
}

void draw_line_xy(int x0, int x1, int y0, int y1)
{
    int x, y;
    int error;
    int ystep;
    int deltax;
    int deltay;

    int steep = abs(y1-y0) > abs(x1-x0);

    if(steep){
        swap(&x0, &y0);
        swap(&x1, &y1);
    }
    if(x0>x1){
        swap(&x0, &x1);
        swap(&y0, &y1);

    }
    
    deltax = abs(x1-x0);
    deltay = abs(y1-y0);
    error = 0;
    
    y = y0;    
    if(y0<y1)
        ystep = 1;
    else 
        ystep = -1;
    for(x=x0; x<=x1; x++){
        if(steep)
            graphic_pixel_set(y,x);
        else
            graphic_pixel_set(x,y);
        error += deltay;
        if (error*2 >= deltax){
            y += ystep;
            error = error-deltax;
        }
    }
}

int abs(int n)
{
    return (n<0)?-n:n;
}

void swap(int *n0, int *n1)
{
    int tmp = *n0;
    *n0 = *n1;
    *n1 = tmp;
}   