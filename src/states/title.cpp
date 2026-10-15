#include <iostream>

#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"

#include "mylib.h"

#include "game.h"
#include "states.h"

SDL_Texture *title_text = NULL;
SDL_Texture *subtitle_text = NULL;
SDL_Texture *instructions_text = NULL;
SDL_Texture *start_text = NULL;

float start_text_y = 0.0f;
bool text_move_down = false;

float start_delay_timer = 1.0f;
const float START_DELAY_TIME = 0.5f;

void title_setup(void) {
	start_delay_timer = 0.0f;
}

void title_init(void) {
  SDL_Surface *tmp_surface = NULL;

  tmp_surface = TTF_RenderText_Solid_Wrapped(title_font, "HALF-MINUTE\nINVADERS", 0, NOKIA_LIGHT, 0);
  title_text = SDL_CreateTextureFromSurface(get_renderer(), tmp_surface);

  SDL_DestroySurface(tmp_surface);

  tmp_surface = TTF_RenderText_Solid(subtitle_font, "[ BLACK LABEL ]", 0, NOKIA_LIGHT);
  subtitle_text = SDL_CreateTextureFromSurface(get_renderer(), tmp_surface);

  SDL_DestroySurface(tmp_surface);

  tmp_surface = TTF_RenderText_Solid_Wrapped(label_font, "<- : Move Left\n-> : Move Right\nSPACE : Shoot", 0, NOKIA_LIGHT, 0);
  instructions_text = SDL_CreateTextureFromSurface(get_renderer(), tmp_surface);

  SDL_DestroySurface(tmp_surface);

  tmp_surface = TTF_RenderText_Solid_Wrapped(label_font, "PRESS Shoot TO\nSTART", 0, NOKIA_LIGHT, 0);
  start_text = SDL_CreateTextureFromSurface(get_renderer(), tmp_surface);

  SDL_DestroySurface(tmp_surface);

  start_text_y = 92.0f;
  text_move_down = true;
}

void title_deinit(void) {
	unload_texture(title_text);
	unload_texture(subtitle_text);
	unload_texture(instructions_text);
	unload_texture(start_text);
}

bool title_update(float dt) {
  if ( shoot_key && !shoot_key_held && start_delay_timer > START_DELAY_TIME ) {
    shoot_key_held = true;
    return true;
  }

	if (start_delay_timer <= START_DELAY_TIME)
		start_delay_timer += dt;
	
  if (text_move_down) {
    start_text_y += 2.0f * dt;
    if (start_text_y > 92.0f)
      text_move_down = false;
  }
  else {
    start_text_y -= 2.0f * dt;
    if (start_text_y < 90.0f)
      text_move_down = true;
  }

  return false;
}

void title_draw(void) {
  draw_texture(title_text, 8.0f, 24.0f);
  draw_texture(subtitle_text, 8.0f, 48.0f);
  draw_texture(instructions_text, 14.0f, 64.0f);
  draw_texture(start_text, 8.0f, start_text_y);
}
