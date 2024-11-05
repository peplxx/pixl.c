#ifndef RECT_PIXL
#define RECT_PIXL
#include <stdlib.h>
#include <stdio.h>
#include "shape.h"


typedef struct Rectangle{
    vec2 ld;
    vec2 ru;
    pixel color;
    void (* render)(struct Rectangle* self,struct FrameBuffer* fb);
} Rectangle;

void render_rectangle(struct Rectangle* self, struct FrameBuffer* fb){
    struct vec2 ld = self->ld,ru = self->ru;

    for (int32_t x=ld.x; x< ru.x; x+=1){
        for (int32_t y=ld.y; y<ru.y; y+=1){
            struct vec2 point = VEC2(x,y);
            fb->render_pixel(fb,point,self->color);
        }
    }
}

struct Rectangle Rectangle_create(vec2 LeftDown, vec2 RightUp, pixel color){
    Rectangle rect = (Rectangle){
        .ld = LeftDown,
        .ru = RightUp,
        .color= color,
        .render = render_rectangle,
    };
    return rect;
}
#endif