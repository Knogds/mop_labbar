#include "font.h"

#define SCREEN_ORIGIN_X 1
#define SCREEN_ORIGIN_Y 1
#define SCREEN_WIDTH 127
#define SCREEN_HEIGHT 64

static char x_pos = SCREEN_ORIGIN_X;
static char y_pos = SCREEN_ORIGIN_Y;
static char x_newline = SCREEN_ORIGIN_X;

void font_render(char x, char y, char c)
{
    int font_val = c * 8;
    for(int i = 0; i<8; i++){
        for(int j = 0; j<6; j++){
            if(font_data[font_val+i] & (1<<(6-j)))
                graphic_pixel_set(x+j, y+i);
            else
                graphic_pixel_clear(x+j, y+i);
        }
    }
}

void font_set_pos(char x, char y){
    x_pos = x;
    x_newline = x;
    y_pos = y;
}

void font_putc(char c){
    if(x_pos +6 > SCREEN_WIDTH){
        x_pos = 0;
    }
    if(c=='\n'){
        if(y_pos+8 < SCREEN_HEIGHT){
            y_pos = y_pos + 8;
            x_pos = x_newline;
        }
    } else {
            
        font_render(x_pos, y_pos, c);
        x_pos += 6;
        
        if(x_pos+6 > SCREEN_WIDTH)
            if(y_pos+8 < SCREEN_HEIGHT)
                y_pos = y_pos + 8;
    }
}
