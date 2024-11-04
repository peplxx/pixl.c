#ifndef FRAMEBUFF_PIXL
#define FRAMEBUFF_PIXL
#include <stdint.h>
#include "primitives/primitives.h"


typedef struct FrameBuffer{
    const uint32_t width, height;
    pixel *buffer;
    
    // Methods
    void (* render_pixel)(FrameBuffer* self, pixel pixel);
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

FrameBuffer FrameBuffer_create(uint32_t width, uint32_t height,pixel color){
    FrameBuffer fb = (FrameBuffer){
        .width = width,
        .height = height,
        .buffer = (pixel*) malloc(width * height * sizeof(pixel)),
        .render_pixel=render_pixel,
        .clear = clear_framebuffer,
        .destroy = destroy_framebuffer,
    };
    fb.clear(&fb, color);
    return fb;
}

void render_pixel(struct FrameBuffer* self, vec2 pos, pixel pixel){
    self->buffer[pos.frame_buffer_index(&pos, self->width)] = pixel;
}
#endif