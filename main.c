#include <stdio.h>
#include "pixl/pixl.h"

int main() {
    Pixl pixl = Pixl_create(1280,1280,"Pixl");
    pixl.display(&pixl);
    return 0;
}
