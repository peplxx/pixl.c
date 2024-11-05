#ifndef LAYER_PIXL
#define LAYER_PIXL
#include "../primitives/primitives.h"

typedef struct Layer{
    int32_t width;
    int32_t height;
    int32_t z_index;
    pixel *buffer;
    struct Layer *next;
    struct Layer *prev;

    // Methods
    void (* clear)(struct Layer *layer);
    void (* destroy)(struct Layer *layer);
    void (* render_pixel)(struct Layer *self, vec2 pos, pixel pixel);
} Layer;
void render_pixel(struct Layer *self, vec2 pos, pixel pixel){
    if (pos.x >= self->width || pos.x < 0 || pos.y >= self->height || pos.y < 0)return;
    self->buffer[pos.x * self->width + pos.y] = pixel;
}
void clear_layer(struct Layer *layer){
    memset(layer->buffer, 0, layer->width * layer->height * sizeof(pixel));
};

void destroy_layer(struct Layer *layer){
    free(layer->buffer);
    free(layer);
}

Layer* Layer_create(int32_t width, int32_t height, int32_t z_index, Layer * previous){ 
    Layer* layer = (Layer*)malloc(sizeof(Layer));
    layer->z_index = z_index;
    layer->width = width;
    layer->height = height;
    layer->buffer = (pixel*)malloc(width * height * sizeof(pixel));
    layer->next = NULL;
    layer->prev = previous;
    if (previous != NULL) previous->next = layer;
    layer->render_pixel = render_pixel;
    layer->clear = clear_layer;
    layer->destroy = destroy_layer;
    return layer;
}
#endif
