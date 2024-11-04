#include <stdint.h>

#ifndef VEC2_PIXL
#define VEC2_PIXL

#define VEC2(x, y) { (x), (y), vec2_frame_buffer_index }

typedef struct vec2{
    int32_t x,y;
    
    int32_t (*frame_buffer_index)(struct vec2 *self, int32_t width);
} vec2;

int32_t vec2_frame_buffer_index(struct vec2 *self, int32_t width){
    return self->y * width + self->x;
}

#endif