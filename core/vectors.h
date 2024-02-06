#pragma once

#define VEC_UP \
    (Vec) { 0, -1 }
#define VEC_DOWN \
    (Vec) { 0, 1 }
#define VEC_LEFT \
    (Vec) { -1, 0 }
#define VEC_RIGHT \
    (Vec) { 1, 0 }

typedef struct
{
    int x, y;
} Vec;
