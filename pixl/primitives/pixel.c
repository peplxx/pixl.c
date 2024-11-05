#include <stdint.h>

#ifndef PIXEL_PIXL
#define PIXEL_PIXL
#define BLACK RGB(0,0,0);
#define RED RGB(255,0,0);
#define GREEN RGB(0,255,0);
#define BLUE RGB(0,0,255);
#define BLACK RGB(0,0,0);

typedef union pixel{
    uint32_t data;
    struct {
        uint8_t a,r,g,b;
    } color;
} pixel;
pixel RGB(uint8_t r, uint8_t g, uint8_t b){
    return (pixel){255<<24|r<<16|g<<8|b};
}
pixel ARGB(uint8_t a,uint8_t r, uint8_t g, uint8_t b){
    return (pixel){a<<24|r<<16|g<<8|b};
}
#endif