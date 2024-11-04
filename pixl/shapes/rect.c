#include <stdlib.h>
#include "shape.h"
#include "primitives/primitives.h"

typedef struct Rectangle{
    Shape base;
    vec2 vertices[4];

} Rectangle;

void render(struct Shape* shape){
    Rectangle * self = (Rectangle * )shape;
    vec2 ld = self->vertices[0],ru = self->vertices[2];
    for (int x=ld.x; x< ru.x; x++){
        for (int y=ld.y; y<ru.y; y++){
            // TODO: Add framebuffer.render_pixel
        }
    }
}

struct Rectangle Rectangle_create(vec2 LeftDown, vec2 RightUp){
    Rectangle rect = (Rectangle){
        .vertices = {
            LeftDown,
            {LeftDown.x, RightUp.y},
            RightUp,
            {RightUp.x, LeftDown.y}
        }

    }
}
