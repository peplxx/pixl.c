#ifndef FRAMEBUFF_PIXL
#define FRAMEBUFF_PIXL
#include <stdint.h>
#include <stdio.h>
#include "../primitives/primitives.h"
#include "layer.h"
#include "../pixl.h"
#define MAX_LAYERS 5


typedef struct FrameBuffer{
    int32_t width;
    int32_t height;
    Layer *layers[MAX_LAYERS]; 
    pixel* buffer;

    // Methods
    void (* render_pixel)(struct FrameBuffer* self, int32_t z_index, vec2 pos, pixel pixel);
    void (* clear)(struct FrameBuffer* self, pixel color);
    void (* destroy)(struct FrameBuffer* self);
    pixel* (* get_buffer)(struct FrameBuffer* self);
} FrameBuffer;


void clear_framebuffer(struct FrameBuffer* self, pixel color){
    for (uint32_t index = 0; index < MAX_LAYERS; index++) {
        if (self->layers[index] != NULL) {
            self->layers[index]->clear(self->layers[index]);
        }
    }
}
void destroy_framebuffer(struct FrameBuffer* self){
    for (uint32_t index = 0; index < MAX_LAYERS; index++){
        if (self->layers[index] != NULL)
            self->layers[index]->destroy(self->layers[index]);
    }
}

void fb_render_pixel(struct FrameBuffer* self, int32_t z_index, struct vec2 pos, pixel pixel){
    if (z_index < 0 || z_index >= MAX_LAYERS) return;
    self->layers[z_index]->render_pixel(self->layers[z_index], pos, pixel);
}

void* get_buffer(struct FrameBuffer* self) {
    for (int32_t x = 0; x < self->width; x++) {
        for (int32_t y = 0; y < self->height; y++) {
            self->buffer[x * self->width + y] = ARGB(0, 0, 0, 0);
            for (int32_t z = MAX_LAYERS - 1; z >= 0; z--) {
                Layer* layer = self->layers[z];
                pixel current_pixel = layer->buffer[x * self->width + y];
                if (current_pixel.data != 0) {
                    self->buffer[x * self->width + y] = current_pixel;
                    break;
                }
            }
        }
    }
    return self->buffer;
}


FrameBuffer* FrameBuffer_create(int32_t width, int32_t height, pixel color){
    FrameBuffer* fb = (FrameBuffer*)malloc(sizeof(FrameBuffer));
    fb->width = width;
    fb->height = height;
    fb->buffer = (pixel*)malloc(fb->width * fb->height * sizeof(pixel));
    for (uint32_t index = 0; index < MAX_LAYERS; index++){
        if (index == 0){
            fb->layers[index] = Layer_create(fb->width, fb->height, index, NULL);
            continue;
        }
        fb->layers[index] = Layer_create(fb->width, fb->height, index, fb->layers[index-1]);
    }
    fb->render_pixel=fb_render_pixel;
    fb->clear = clear_framebuffer;
    fb->destroy = destroy_framebuffer;
    fb->get_buffer = get_buffer;
    clear_framebuffer(fb, color);
    return fb;
}

#endif