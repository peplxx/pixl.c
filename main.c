#include "pixl/pixl.h"

int main() {
    Pixl pixl = Pixl_create(1280,1280,"Pixl",RGB(0,255,0));
    pixl.display(&pixl);
    return 0;
}
