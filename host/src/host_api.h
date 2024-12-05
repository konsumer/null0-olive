// Host interface exposed to WAMR and Emscripten

#pragma once

static cvector_vector_type(Olivec_Canvas) canvases = NULL;

uint32_t add_canvas(Olivec_Canvas canvas) {
  uint32_t id = cvector_size(canvases);
  cvector_push_back(canvases, canvas);
  return id;
}

// OLIVEC
