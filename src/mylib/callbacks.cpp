#include <iostream>

#include "mylib.h"

#include "SDL3/SDL.h"

SDL_Event event;

double frame_time = 0.0;
double accumulator = 0.0;
float delta_time = 0.0;

void run(void) {
  if ( window_should_close() ) {
    game_close();
  }

  tick_clock();

  handle_events(event);

  accumulator += get_frame_time();
  
  while (accumulator >= get_target_frame_time()) {
    delta_time = static_cast<float>( get_target_frame_time() );
    update(delta_time);
    accumulator -= get_target_frame_time();
  }

  draw();

#ifndef __EMSCRIPTEN__
  cap_fps();
#endif
}
