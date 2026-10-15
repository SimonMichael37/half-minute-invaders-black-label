#include "mylib.h"

#include "SDL3/SDL.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

int main(int argc, char **argv) {
  game_init();

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(run, 0, true);
#else
  while (true) {
    run();
  }
#endif

  game_close();

  return 0;
}
