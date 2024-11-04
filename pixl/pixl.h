#include <SDL2/SDL.h>

typedef struct Pixl{
    const uint32_t Width, Height;
    const char* Title;
    SDL_Window *window;
    SDL_Renderer *renderer;
    uint8_t is_running;

    // Methods
    void (* init)(struct Pixl *self);
    void (* display)(struct Pixl *self);
    void (* destroy)(struct Pixl *self);
} Pixl;

void init(struct Pixl*self){
    self->window = SDL_CreateWindow(self->Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, self->Width, self->Height, SDL_WINDOW_SHOWN);
    self->renderer = SDL_CreateRenderer(self->window, -1, SDL_RENDERER_ACCELERATED);
}
void display(struct Pixl*self){
    self->is_running = 1;
    SDL_Event event;
    while (self->is_running ){
        while ( SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT) self->is_running = 0;
        }
        SDL_RenderPresent(self->renderer);
    }
    self->destroy(self);
    
}
void destroy(struct Pixl*self){
    SDL_DestroyRenderer(self->renderer);
    SDL_DestroyWindow(self->window);
    SDL_Quit();
}


static Pixl Pixl_create(
    uint32_t width,
    uint32_t height,
    const char* title
){
    Pixl pixl = (Pixl){
        .Width=width,
        .Height=height,
        .Title=title,
        .window=NULL,
        .renderer=NULL,
        .is_running=0,
        .init=init,
        .display=display,
        .destroy=destroy
    };
    pixl.init(&pixl);
    return pixl;
}