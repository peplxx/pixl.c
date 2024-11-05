#include "pixl/pixl.h"
#include "pixl/shapes/shapes.h"
#define PIXL_DEBUG


int main() {
    Pixl pixl = Pixl_create(1280,1280,"Pixl",RGB(0,255,0));
    Rectangle rect = Rectangle_create(VEC2(140,140),VEC2(1140,1140),RGB(0,0,0));
    rect.render(&rect, pixl.frameBuffer);
    pixl.display(&pixl);
    return 0;
}
