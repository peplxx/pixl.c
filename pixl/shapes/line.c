#ifndef PIXL_LINE
#define PIXL_LINE
#include "shape.h"
#include "../render/framebuffer.h"
#include "../primitives/primitives.h"


typedef struct Line{
    vec2 start;
    vec2 end;
    int32_t thickness;
    pixel color;
    Shape base;    
}Line;

void render_line(struct Shape* self, struct FrameBuffer* fb, int32_t z_index){
    Line* line = (Line*) self;
    struct vec2 start = line->start, end = line->end;
    int32_t dx = abs(end.x - start.x);
    int32_t dy = abs(end.y - start.y);
    int32_t sx = (end.x >= start.x) ? 1 : -1;
    int32_t sy = (end.y >= start.y) ? 1 : -1;
    int32_t err = dx - dy;
    int32_t x = start.x;
    int32_t y = start.y;
    int32_t r = 0;
    while (x != end.x || y != end.y){
        fb->render_pixel(fb, z_index, VEC2(x, y), line->color); 
        int32_t e2 = err * 2;
        if (e2 > -dy){
            err -= dy;
            x += sx;
        }
        if (e2 < dx){
            err += dx;
            y += sy;
        }
    }
}

struct Line Line_create(vec2 start, vec2 end, int32_t thickness, pixel color){
    Line line = (Line){
        .start = start,
        .end = end,
        .thickness = thickness,
        .color = color,
        .base = {.render=render_line},
    };
    return line;
}


#endif