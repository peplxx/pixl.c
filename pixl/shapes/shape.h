#ifndef SHAPE_PIXL
#define SHAPE_PIXL
#include "../render/framebuffer.h"

typedef struct Shape{
    void (* render)(struct Shape* self,struct FrameBuffer* fb, int32_t z_index);
} Shape;    
#endif
