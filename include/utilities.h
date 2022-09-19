#ifndef UTILITIES_H
#define UTILITIES_H

#include <Windows.h>

typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;;

#define global_variable static
#define internal static

struct GlobalVars {
    bool window_running;
};
extern GlobalVars global_vars;

struct RenderState {
    int height, width;
    void* memory;
    BITMAPINFO bitmap_info;
};
extern RenderState render_state;

inline int
clamp(int val, int min, int max) {
    if (val < min) return min;
    if (val > max) return max;
    return val;
}

#endif
