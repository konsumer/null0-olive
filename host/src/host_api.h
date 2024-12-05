// Host interface exposed to WAMR and Emscripten

#pragma once

static cvector_vector_type(Olivec_Canvas) canvases = NULL;
static cvector_vector_type(Olivec_Font) fonts = NULL;

uint32_t add_canvas(Olivec_Canvas canvas) {
  uint32_t id = cvector_size(canvases);
  cvector_push_back(canvases, canvas);
  return id;
}

// OLIVEC

// called in setup to initialize default font & screen
void null0_setup_graphics() {
  uint32_t *pixels = malloc(640 * 480 * sizeof(uint32_t));
  add_canvas(olivec_canvas(pixels, 640, 480, 640));
  cvector_push_back(fonts, olivec_default_font);
}

Olivec_Canvas null0_get_screen() {
  return canvases[0];
}


HOST_FUNCTION(uint32_t, new_canvas, (size_t width, size_t height), {
  uint32_t *pixels = malloc(width * height * sizeof(uint32_t));
  return add_canvas(olivec_canvas(pixels, width, height, width));
})

HOST_FUNCTION(uint32_t, subcanvas, (uint32_t oc, int x, int y, int w, int h), {
  return add_canvas(olivec_subcanvas(canvases[oc], x, y, w, h));
})

HOST_FUNCTION(bool, in_bounds, (uint32_t oc, int x, int y), {
  return olivec_in_bounds(canvases[oc], x, y);
})

HOST_FUNCTION(void, blend_color, (uint32_t c1Pointer, uint32_t c2), {
  uint32_t c1 = 0;
  olivec_blend_color(&c1, c2);
  copy_to_cart_with_pointer(c1Pointer, &c1, sizeof(uint32_t));
})

HOST_FUNCTION(void, fill, (uint32_t oc, uint32_t color), {
  olivec_fill(canvases[oc], color);
})

HOST_FUNCTION(void, rect, (uint32_t oc, int x, int y, int w, int h, uint32_t color), {
  olivec_rect(canvases[oc], x, y, w, h, color);
})

HOST_FUNCTION(void, frame, (uint32_t oc, int x, int y, int w, int h, size_t thiccness, uint32_t color), {
  olivec_frame(canvases[oc], x, y, w, h, thiccness, color);
})

HOST_FUNCTION(void, circle, (uint32_t oc, int cx, int cy, int r, uint32_t color), {
  olivec_circle(canvases[oc], cx, cy, r, color);
})

HOST_FUNCTION(void, ellipse, (uint32_t oc, int cx, int cy, int rx, int ry, uint32_t color), {
  olivec_ellipse(canvases[oc], cx, cy, rx, ry, color);
})

HOST_FUNCTION(void, line, (uint32_t oc, int x1, int y1, int x2, int y2, uint32_t color), {
  olivec_line(canvases[oc], x1, y1, x2, y2, color);
})

HOST_FUNCTION(bool, normalize_triangle, (size_t width, size_t height, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t lxPtr, uint32_t hxPtr, uint32_t lyPtr, uint32_t hyPtr), {
  int lx = 0;
  int hx = 0;
  int ly = 0;
  int hy = 0;
  bool ret = olivec_normalize_triangle(width, height, x1, y1, x2, y2, x3, y3, &lx, &hx, &ly, &hy);
  copy_to_cart_with_pointer(lxPtr, &lx, sizeof(int));
  copy_to_cart_with_pointer(hxPtr, &hx, sizeof(int));
  copy_to_cart_with_pointer(lyPtr, &ly, sizeof(int));
  copy_to_cart_with_pointer(hyPtr, &hy, sizeof(int));
  return ret;
})

HOST_FUNCTION(bool, barycentric, (int x1, int y1, int x2, int y2, int x3, int y3, int xp, int yp, uint32_t u1Ptr, uint32_t u2Ptr, uint32_t detPtr), {
  int u1 = 0;
  int u2 = 0;
  int det = 0;
  bool ret = olivec_barycentric(x1, y1, x2, y2, x3, y3, xp, yp, &u1, &u2, &det);
  copy_to_cart_with_pointer(u1Ptr, &u1, sizeof(int));
  copy_to_cart_with_pointer(u2Ptr, &u2, sizeof(int));
  copy_to_cart_with_pointer(detPtr, &det, sizeof(int));
  return ret;
})

HOST_FUNCTION(void, triangle, (uint32_t oc, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color), {
  olivec_triangle(canvases[oc],  x1,  y1,  x2,  y2,  x3,  y3,  color);
})

HOST_FUNCTION(void, triangle3c, (uint32_t oc, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c1, uint32_t c2, uint32_t c3), {
  olivec_triangle3c(canvases[oc],  x1,  y1,  x2,  y2,  x3,  y3,  c1,  c2,  c3);
})

HOST_FUNCTION(void, triangle3z, (uint32_t oc, int x1, int y1, int x2, int y2, int x3, int y3, float z1, float z2, float z3), {
  olivec_triangle3z(canvases[oc],  x1,  y1,  x2,  y2,  x3,  y3,  z1,  z2,  z3);
})

HOST_FUNCTION(void, triangle3uv, (uint32_t oc, int x1, int y1, int x2, int y2, int x3, int y3, float tx1, float ty1, float tx2, float ty2, float tx3, float ty3, float z1, float z2, float z3, uint32_t texture), {
  olivec_triangle3uv(canvases[oc],  x1,  y1,  x2,  y2,  x3,  y3,  tx1,  ty1,  tx2,  ty2,  tx3,  ty3,  z1,  z2,  z3, canvases[texture]);
})

HOST_FUNCTION(void, triangle3uv_bilinear, (uint32_t oc, int x1, int y1, int x2, int y2, int x3, int y3, float tx1, float ty1, float tx2, float ty2, float tx3, float ty3, float z1, float z2, float z3, uint32_t texture), {
  olivec_triangle3uv_bilinear(canvases[oc],  x1,  y1,  x2,  y2,  x3,  y3,  tx1,  ty1,  tx2,  ty2,  tx3,  ty3,  z1,  z2,  z3, canvases[texture]);
})

HOST_FUNCTION(void, text, (uint32_t oc, uint32_t textPtr, int x, int y, uint32_t font, size_t size, uint32_t color), {
  char* text = copy_from_cart_string(textPtr);
  olivec_text(canvases[oc], text, x,  y, fonts[font],  size,  color);
  free(text);
})

HOST_FUNCTION(void, sprite_blend, (uint32_t oc, int x, int y, int w, int h, uint32_t sprite), {
  olivec_sprite_blend(canvases[oc],  x,  y,  w,  h, canvases[sprite]);
})

HOST_FUNCTION(void, sprite_copy, (uint32_t oc, int x, int y, int w, int h, uint32_t sprite), {
  olivec_sprite_copy(canvases[oc],  x,  y,  w,  h, canvases[sprite]);
})

HOST_FUNCTION(void, sprite_copy_bilinear, (uint32_t oc, int x, int y, int w, int h, uint32_t sprite), {
  olivec_sprite_copy_bilinear(canvases[oc],  x,  y,  w,  h, canvases[sprite]);
})

HOST_FUNCTION(uint32_t, pixel_bilinear, (uint32_t sprite, int nx, int ny, int w, int h), {
  return olivec_pixel_bilinear(canvases[sprite],  nx,  ny,  w,  h);
})
