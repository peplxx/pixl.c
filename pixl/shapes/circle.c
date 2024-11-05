#ifndef CIRCLE_PIXL
#define CIRCLE_PIXL
#include "shape.h"


typedef struct Circle{
    vec2 center;
    int32_t radius;
    pixel color;
    Shape base;
} Circle;

void render_circle(struct Shape* self, struct FrameBuffer* fb, int32_t z_index){
    Circle* circle = (Circle*) self;
    vec2 center = circle->center;
    int32_t radius = circle->radius;

    int32_t x = 0;
    int32_t y = radius;
    int32_t d = 3 - 2 * radius;
    while (x <= y){
        fb->render_pixel(fb, z_index, VEC2(x + center.x, y + center.y), circle->color);
        fb->render_pixel(fb, z_index, VEC2(y + center.x, x + center.y), circle->color);
        fb->render_pixel(fb, z_index, VEC2(-x + center.x, y + center.y), circle->color);
        fb->render_pixel(fb, z_index, VEC2(-y + center.x, x + center.y), circle->color);
        fb->render_pixel(fb, z_index, VEC2(x + center.x, -y + center.y), circle->color);
        fb->render_pixel(fb, z_index, VEC2(y + center.x, -x + center.y), circle->color);
        fb->render_pixel(fb, z_index, VEC2(-x + center.x, -y + center.y), circle->color);
        fb->render_pixel(fb, z_index, VEC2(-y + center.x, -x + center.y), circle->color);
        if (d < 0){
            d += 4 * x + 6;
        }else{
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}
struct Circle Circle_create(vec2 center, int32_t radius, pixel color){
    struct Circle circle = {
        .center = center,
        .radius = radius,
        .color = color,
        .base = {
            .render = render_circle,
        },
    };
    return circle;
}


#endif