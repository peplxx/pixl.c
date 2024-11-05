
#ifndef MATH_PIXL
#define MATH_PIXL
#include <stdint.h>


int32_t min(int32_t a,int32_t b){
    if (a < b)
        return a;
    return b;
}
int32_t max(int32_t a,int32_t b){
    if (a > b)
        return a;
    return b;
}

#endif