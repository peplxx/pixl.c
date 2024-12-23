#include "pixl/pixl.h"

// #define DEBUG 
#include "pixl/utils/debug.h"

// Simple drawer example

#define UI_LAYER MAX_LAYERS-1
#define GRAPHICS_LAYER MAX_LAYERS-2

int BRUSH = 20;
vec2 start = VEC2(-1, -1);
int isPressed = 0;

pixel blendColors(pixel color1, pixel color2, float t) {
    return RGB(
        (1 - t) * color1.color.r + t * color2.color.r,
        (1 - t) * color1.color.g + t * color2.color.g,
        (1 - t) * color1.color.b + t * color2.color.b
    );
}

pixel getFinalColor(vec2 mouse, int width, int height) {
    float t1 = (float)mouse.x / width;
    float t2 = (float)mouse.y / height;
    
    pixel blend1 = blendColors(RGB(255, 0, 0), RGB(0, 255, 0), t1);
    return blendColors(blend1, RGB(0, 0, 255), t2);
}

void onUpdate(struct Pixl* self, SDL_Event* event) {
    FrameBuffer* fb = self->frameBuffer;
    vec2 mouse = self->mouse;
    
    pixel finalColor = getFinalColor(mouse, self->Width, self->Height);

    fb->layers[UI_LAYER]->clear(fb->layers[UI_LAYER]);

    if (isPressed) {
        Circle circle = Circle_create(mouse, BRUSH, finalColor);
        circle.base.render(&circle, self->frameBuffer, GRAPHICS_LAYER);
    } else {
        Circle ui = Circle_create(mouse, BRUSH, finalColor);
        ui.base.render(&ui, self->frameBuffer, UI_LAYER);
    }
}

void onMouseDown(struct Pixl* self, SDL_Event* event) {
    dprintf("Mouse Down! (%d, %d) brush size: %d\n", event->motion.x, event->motion.y, BRUSH);
    isPressed = 1;
    start = self->mouse;
}

void onMouseUp(struct Pixl* self, SDL_Event* event) {
    dprintf("Mouse Up! (%d, %d)\n", event->motion.x, event->motion.y);
    isPressed = 0;
}

void onMouseWheel(struct Pixl* self, SDL_Event* event) {
    BRUSH += event->wheel.y;
    dprintf("Brush size is now %d\n", BRUSH); 
}

int main() {
    Pixl pixl = Pixl_create(1000, 1000, "Pixl-Drawer", RGB(20, 20, 20));
    pixl.onUpdate = onUpdate;
    pixl.onMouseDown = onMouseDown;
    pixl.onMouseUp = onMouseUp;
    pixl.onMouseWheel = onMouseWheel;

    pixl.display(&pixl);
    return 0;
}
