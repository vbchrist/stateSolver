
#include <emscripten.h>

extern "C" {

// Not using size_t for array indices as the values used by the javascript code are signed.
void array_bounds_check(const int array_size, const int array_idx) {
  if (array_idx < 0 || array_idx >= array_size) {
    EM_ASM({
      throw 'Array index ' + $0 + ' out of bounds: [0,' + $1 + ')';
    }, array_idx, array_size);
  }
}

// web_interface

web_interface* EMSCRIPTEN_KEEPALIVE emscripten_bind_web_interface_web_interface_0() {
  return new web_interface();
}

const char* EMSCRIPTEN_KEEPALIVE emscripten_bind_web_interface_get_vals_1(web_interface* self, const char* arg0) {
  return self->get_vals(arg0);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_web_interface___destroy___0(web_interface* self) {
  delete self;
}

// VoidPtr

void EMSCRIPTEN_KEEPALIVE emscripten_bind_VoidPtr___destroy___0(void** self) {
  delete self;
}

}

