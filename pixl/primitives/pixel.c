#include <stdint.h>

#ifndef PIXEL_PIXL
#define PIXEL_PIXL
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
#endif