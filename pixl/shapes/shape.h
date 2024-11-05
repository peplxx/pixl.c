#ifndef SHAPE_PIXL
#define SHAPE_PIXL
#include "../framebuffer.c"

typedef struct Shape{
    void (* render)(struct Shape* self,struct FrameBuffer* fb);
} Shape;    
#endif