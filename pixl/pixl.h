
#ifndef MAIN_PIXL
#define MAIN_PIXL
#include <SDL2/SDL.h>
#include "framebuffer.c"

struct Pixl* canvas = NULL;
const struct Pixl* get_canvas(){
    return canvas;
}


typedef struct Pixl{
    const uint32_t Width, Height;
    const char* Title;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    struct FrameBuffer *frameBuffer;
    uint8_t is_running;

    // Methods
    void (* init)(struct Pixl *self);
    void (* display)(struct Pixl *self);
    void (* destroy)(struct Pixl *self);
} Pixl;

void init(struct Pixl*self){
    self->window = SDL_CreateWindow(self->Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, self->Width, self->Height, SDL_WINDOW_SHOWN);
    self->renderer = SDL_CreateRenderer(self->window, -1, SDL_RENDERER_ACCELERATED);
    self->texture = SDL_CreateTexture(self->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, self->Width, self->Height);
}
void display(struct Pixl*self){
    self->is_running = 1;
    SDL_Event event;
    SDL_UpdateTexture(self->texture, NULL, self->frameBuffer->buffer, self->Width * sizeof(pixel));
    SDL_RenderCopy(self->renderer, self->texture, NULL, NULL);
    SDL_RenderPresent(self->renderer);
    while (self->is_running ){
        while ( SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT) self->is_running = 0;
        }
        
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


static Pixl Pixl_create(
    uint32_t width,
    uint32_t height,
    const char* title,
    pixel color
){
    if (canvas)return *canvas;
    FrameBuffer fb = FrameBuffer_create(width, height, color);
    Pixl pixl = (Pixl){
        .Width=width,
        .Height=height,
        .Title=title,
        .window=NULL,
        .renderer=NULL,
        .frameBuffer=&fb,
        .is_running=0,
        .init=init,
        .display=display,
        .destroy=destroy,
    };
    pixl.init(&pixl);
    canvas = &pixl;
    return pixl;
    
}
#endif