#include "pixl/pixl.h"
#include "pixl/shapes/shapes.h"
#define PIXL_DEBUG

int BRUSH = 20;
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
    if (isPressed){
        Circle rect = Circle_create(mouse, BRUSH, finalColor);
        rect.base.render(&rect, self->frameBuffer, 0);
    }
    // if (event.type)return; // skip clearing when scrolling
    fb->layers[MAX_LAYERS-1]->clear(fb->layers[MAX_LAYERS-1]);
    Circle ui = Circle_create(mouse, BRUSH, RGB(255, 255, 255));
    ui.base.render(&ui, self->frameBuffer, MAX_LAYERS-1);

}

void onMouseDown(struct Pixl* self, SDL_Event* event){
    // printf("Mouse Down! (%d, %d)\n",event->motion.x, event->motion.y);
    isPressed = 1;
}
void onMouseUp(struct Pixl* self, SDL_Event* event){
    // printf("Mouse Up! (%d, %d)\n",event->motion.x, event->motion.y);
    isPressed = 0;
}

void onMouseWheel(struct Pixl* self, SDL_Event* event){
    // printf("Brush size is %d\n", BRUSH);
    BRUSH += event->wheel.y;
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
