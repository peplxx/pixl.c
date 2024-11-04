#ifndef SHAPE_PIXL
#define SHAPE_PIXL

typedef struct Shape{
    void (* render)(struct Shape* self);
} Shape;    
#endif