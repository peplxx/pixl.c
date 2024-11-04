#include <SDL2/SDL.h>

typedef struct Pixl{
    const uint32_t Width, Height;
    const char* Title;
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool is_running;

    void (* init)(struct Pixl *self);
    void (* display)(struct Pixl *self);
    void (* destroy)(struct Pixl *self);
} Pixl;

void init(struct Pixl*self){return;}
void display(struct Pixl*self){return;}
void destroy(struct Pixl*self){return;}


Pixl create_pixl(
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
        .is_running=false,
        .init=init,
        .display=display,
        .destroy=destroy,
    };
    pixl.init(&pixl);
    return pixl;
}