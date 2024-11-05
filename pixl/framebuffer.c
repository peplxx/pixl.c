#ifndef FRAMEBUFF_PIXL
#define FRAMEBUFF_PIXL
#include <stdint.h>
#include <stdio.h>
#include "primitives/primitives.h"


typedef struct FrameBuffer{
    int32_t width;
    int32_t height;
    pixel *buffer;
    
    // Methods
    void (* render_pixel)(struct FrameBuffer* self, vec2 pos, pixel pixel);
    void (* clear)(struct FrameBuffer* self, pixel color);
    void (* destroy)(struct FrameBuffer* self);

} FrameBuffer;


void clear_framebuffer(struct FrameBuffer* self, pixel color){
    for (uint32_t index = 0; index < self->height*self->width;index++){
        self->buffer[index] = color;
    }
}
void destroy_framebuffer(struct FrameBuffer* self){
    free(self->buffer);
}

void render_pixel(struct FrameBuffer* self, struct vec2 pos, pixel pixel){
    if (pos.x >= self->width || pos.x < 0 || pos.y >= self->height || pos.y < 0)return;
    self->buffer[pos.x * self->width + pos.y] = pixel;
}

FrameBuffer* FrameBuffer_create(int32_t width, int32_t height,pixel color){
    FrameBuffer* fb = (FrameBuffer*)malloc(sizeof(FrameBuffer));
    fb->width = width;
    fb->height = height;
    fb->buffer = (pixel*) malloc(width * height * sizeof(pixel));
    fb->render_pixel=render_pixel;
    fb->clear = clear_framebuffer;
    fb->destroy = destroy_framebuffer;

    fb->clear(fb, color);
    return fb;
}

#endif