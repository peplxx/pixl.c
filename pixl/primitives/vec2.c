#include <stdint.h>

#ifndef VEC2_PIXL
#define VEC2_PIXL

#define VEC2(x, y) (vec2) { (x), (y) }

typedef struct vec2{
    int32_t x,y;
    
} vec2;

#endif