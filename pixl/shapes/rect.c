#ifndef RECT_PIXL
#define RECT_PIXL
#include <stdlib.h>
#include <stdio.h>
#include "shape.h"
#include "../utils/math.c"

typedef struct Rectangle{
    vec2 ld;
    vec2 ru;
    pixel color;
    Shape base;
} Rectangle;

void render_rectangle(struct Shape* self, struct FrameBuffer* fb, int32_t z_index){
    Rectangle* rect = (Rectangle*) self;
    struct vec2 ld = rect->ld,ru = rect->ru;

    for (int32_t x=ld.x; x< min(ru.x,fb->width); x+=1){
        for (int32_t y=ld.y; min(y<ru.y,fb->height); y+=1){
            struct vec2 point = VEC2(x,y);
            fb->render_pixel(fb,z_index,point,rect->color);
        }
    }
}

struct Rectangle Rectangle_create(vec2 LeftDown, vec2 RightUp, pixel color){
    Rectangle rect = (Rectangle){
        .ld = LeftDown,
        .ru = RightUp,
        .color= color,
        .base = {.render=render_rectangle},
    };
    return rect;
}
struct Rectangle Square_create(vec2 LeftDown, int32_t side, pixel color){
    Rectangle rect = (Rectangle){
        .ld = LeftDown,
        .ru = VEC2(LeftDown.x + side, LeftDown.y + side),
        .color= color,
        .base = {.render=render_rectangle},
    };
    return rect;
};


#endif