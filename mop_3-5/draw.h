#ifndef DRAW_H
#define DRAW_H

typedef struct {
    char x;
    char y;
} point, *ppoint;

typedef struct {
    point xy0;
    point xy1;
} line, *pline;

typedef struct {
    point origo;
    char width;
    char height;
} rect, *prect;

typedef struct polygonpoint {
    point xy;
    struct polygonpoint *next;
} polypoint, *ppolypoint;

void draw_line(pline);
void draw_rect(prect);
int draw_polygon(ppolypoint);
void draw_line_xy(int x0, int x1, int y0, int y1);

#endif