
#ifndef MAIN_PIXL
#define MAIN_PIXL
#include <SDL2/SDL.h>
#include "framebuffer.c"
#include "utils/constraints.h"

struct Pixl* canvas = NULL;
const struct Pixl* get_canvas(){
    return canvas;
}


typedef struct Pixl{
    const int32_t Width, Height;
    int32_t ticks;
    const char* Title;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    struct FrameBuffer *frameBuffer;
    uint8_t is_running;

    // Methods
    void (* init)(struct Pixl *self);
    void (* display)(struct Pixl *self);
    void (* update)(struct Pixl* self);
    void (* destroy)(struct Pixl *self);
    
    // User overridable funcs
    void (* onUpdate)(struct Pilx* self, SDL_Event *event);
    void (* onMouseDown)(struct Pilx* self, SDL_Event *event);
    void (* onMouseUp)(struct Pilx* self, SDL_Event *event);
    void (* onMouseWheel)(struct Pilx* self, SDL_Event *event);

} Pixl;

void init(struct Pixl*self){
    self->window = SDL_CreateWindow(self->Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, self->Width, self->Height, SDL_WINDOW_SHOWN);
    self->renderer = SDL_CreateRenderer(self->window, -1, SDL_RENDERER_ACCELERATED);
    self->texture = SDL_CreateTexture(self->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, self->Width, self->Height);
}
void display(struct Pixl*self){
    self->is_running = 1;
    SDL_Event event;
    while (self->is_running ){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT) self->is_running = 0;
            if (self->onMouseDown != NULL && event.type == SDL_MOUSEBUTTONDOWN)self->onMouseDown(self,&event);
            if (self->onMouseUp != NULL && event.type == SDL_MOUSEBUTTONUP)self->onMouseUp(self,&event); 
            if (self->onMouseWheel != NULL && event.type == SDL_MOUSEWHEEL)self->onMouseWheel(self,&event);
            
            
            
            
            if (self->onUpdate != NULL) 
                self->onUpdate(self, &event); // User defined func for changing buffer.
        
        }
        self->update(self);
    }
    self->destroy(self);
    
}
void destroy(struct Pixl*self){
    SDL_DestroyTexture(self->texture);
    SDL_DestroyRenderer(self->renderer);
    SDL_DestroyWindow(self->window);
    self->frameBuffer->destroy((FrameBuffer*)self->frameBuffer);
    SDL_Quit();
}

void update(struct Pixl* self){
    self->ticks+=1;
    SDL_UpdateTexture(self->texture, NULL, self->frameBuffer->buffer, self->Width * sizeof(pixel));
    SDL_RenderCopy(self->renderer, self->texture, NULL, NULL);
    SDL_RenderPresent(self->renderer);
}
static Pixl Pixl_create(
    int32_t width,
    int32_t height,
    const char* title,
    pixel color
){
    if (canvas)return *canvas;
    FrameBuffer *fb = FrameBuffer_create(width, height, color);

    Pixl pixl = (Pixl){
        .Width=width,
        .Height=height,
        .ticks=0,
        .Title=title,
        .window=NULL,
        .renderer=NULL,
        .frameBuffer=fb,
        .is_running=0,
        .init=init,
        .display=display,
        .update=update,
        .destroy=destroy,

        .onUpdate=NULL,
        .onMouseDown=NULL,
        .onMouseUp=NULL,
        .onMouseWheel=NULL,
    };
    
    pixl.init(&pixl);
    canvas = &pixl;
    return pixl;
}
#endif