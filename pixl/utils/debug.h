#ifndef PIXL_DEBUG  
#define PIXL_DEBUG


#ifdef DEBUG
#define dprintf(...) printf(__VA_ARGS__)
#else
#define dprintf(...) do {} while (0)
#endif


#endif