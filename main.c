#include "pixl/pixl.h"
#include "pixl/shapes/shapes.h"

#define DEBUG
#include "pixl/utils/debug.h"

int BRUSH = 20;
vec2 start = VEC2(-1, -1);
int isPressed = 0;

void onUpdate(struct Pixl* self, SDL_Event* event){
    FrameBuffer* fb = self->frameBuffer;
    vec2 mouse = self->mouse;
    pixel Color1 = RGB(255, 0, 0);
    pixel Color2 = RGB(0, 255, 0); 
    pixel Color3 = RGB(0, 0, 255);
    
    float t1 = (float)mouse.x / self->Width;   // Horizontal factor
    float t2 = (float)mouse.y / self->Height;  // Vertical factor

    pixel blend1 = RGB(
        (1 - t1) * Color1.color.r + t1 * Color2.color.r,
        (1 - t1) * Color1.color.g + t1 * Color2.color.g,
        (1 - t1) * Color1.color.b + t1 * Color2.color.b
    );

    pixel finalColor = RGB(
        (1 - t2) * blend1.color.r + t2 * Color3.color.r,
        (1 - t2) * blend1.color.g + t2 * Color3.color.g,
        (1 - t2) * blend1.color.b + t2 * Color3.color.b
    );
    fb->layers[MAX_LAYERS-1]->clear(fb->layers[MAX_LAYERS-1]);
    if (isPressed){
        Line line = Line_create(start, mouse, BRUSH, finalColor);
        line.base.render(&line, self->frameBuffer, MAX_LAYERS-1);
    }
    else{
        Circle ui = Circle_create(mouse, BRUSH, finalColor);
        ui.base.render(&ui, self->frameBuffer, MAX_LAYERS-1);
    }
}

void onMouseDown(struct Pixl* self, SDL_Event* event){
    dprintf("Mouse Down! (%d, %d) brush size: %d\n",event->motion.x, event->motion.y, BRUSH);
    isPressed = 1;
    start = self->mouse;
}
void onMouseUp(struct Pixl* self, SDL_Event* event){
    dprintf("Mouse Up! (%d, %d)\n",event->motion.x, event->motion.y);
    isPressed = 0;
    Line line = Line_create(start, self->mouse, BRUSH, WHITE);
    line.base.render(&line, self->frameBuffer, MAX_LAYERS-2);
}

void onMouseWheel(struct Pixl* self, SDL_Event* event){
    dprintf("Brush size is now %d\n", BRUSH += event->wheel.y);
}
int main() {
    Pixl pixl = Pixl_create(1000,1000,"Pixl",RGB(20,20,20));
    pixl.onUpdate = onUpdate;
    pixl.onMouseDown = onMouseDown;
    pixl.onMouseUp = onMouseUp;
    pixl.onMouseWheel = onMouseWheel;

    pixl.display(&pixl);
    return 0;
}
