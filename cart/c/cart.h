#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// import function from host
#define HOST_FUNCTION(return_type, name, params) __attribute__((import_module("null0"), import_name(#name))) return_type name params;

// export function to host
#define CART_FUNCTION(n) __attribute__((export_name(n)))

// mem-management

CART_FUNCTION("malloc")
void* _wasm_host_malloc(size_t size) {
  return malloc(size);
}

CART_FUNCTION("free")
void _wasm_host_free(void* ptr) {
  free(ptr);
}

// callbacks
CART_FUNCTION("load")
void load();

CART_FUNCTION("update")
void update(uint64_t timeMS);

CART_FUNCTION("unload")
void unload();

HOST_FUNCTION(uint32_t, new_canvas, (size_t width, size_t height))
HOST_FUNCTION(uint32_t, subcanvas, (uint32_t oc, int x, int y, int w, int h))
HOST_FUNCTION(bool, in_bounds, (uint32_t oc, int x, int y))
HOST_FUNCTION(void, blend_color, (uint32_t c1Pointer, uint32_t c2))
HOST_FUNCTION(void, fill, (uint32_t oc, uint32_t color))
HOST_FUNCTION(void, rect, (uint32_t oc, int x, int y, int w, int h, uint32_t color))
HOST_FUNCTION(void, frame, (uint32_t oc, int x, int y, int w, int h, size_t thiccness, uint32_t color))
HOST_FUNCTION(void, circle, (uint32_t oc, int cx, int cy, int r, uint32_t color))
HOST_FUNCTION(void, ellipse, (uint32_t oc, int cx, int cy, int rx, int ry, uint32_t color))
HOST_FUNCTION(void, line, (uint32_t oc, int x1, int y1, int x2, int y2, uint32_t color))
HOST_FUNCTION(bool, normalize_triangle, (size_t width, size_t height, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t lxPtr, uint32_t hxPtr, uint32_t lyPtr, uint32_t hyPtr))
HOST_FUNCTION(bool, barycentric, (int x1, int y1, int x2, int y2, int x3, int y3, int xp, int yp, uint32_t u1Ptr, uint32_t u2Ptr, uint32_t detPtr))
HOST_FUNCTION(void, triangle, (uint32_t oc, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color))
HOST_FUNCTION(void, triangle3c, (uint32_t oc, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c1, uint32_t c2, uint32_t c3))
HOST_FUNCTION(void, triangle3z, (uint32_t oc, int x1, int y1, int x2, int y2, int x3, int y3, float z1, float z2, float z3))
HOST_FUNCTION(void, triangle3uv, (uint32_t oc, int x1, int y1, int x2, int y2, int x3, int y3, float tx1, float ty1, float tx2, float ty2, float tx3, float ty3, float z1, float z2, float z3, uint32_t texture))
HOST_FUNCTION(void, triangle3uv_bilinear, (uint32_t oc, int x1, int y1, int x2, int y2, int x3, int y3, float tx1, float ty1, float tx2, float ty2, float tx3, float ty3, float z1, float z2, float z3, uint32_t texture))
HOST_FUNCTION(void, text, (uint32_t oc, uint32_t textPtr, int x, int y, uint32_t font, size_t size, uint32_t color))
HOST_FUNCTION(void, sprite_blend, (uint32_t oc, int x, int y, int w, int h, uint32_t sprite))
HOST_FUNCTION(void, sprite_copy, (uint32_t oc, int x, int y, int w, int h, uint32_t sprite))
HOST_FUNCTION(void, sprite_copy_bilinear, (uint32_t oc, int x, int y, int w, int h, uint32_t sprite))
HOST_FUNCTION(uint32_t, pixel_bilinear, (uint32_t sprite, int nx, int ny, int w, int h))