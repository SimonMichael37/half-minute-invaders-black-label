#include <cstdio>

#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"

#include "mylib.h"

#include "game.h"
#include "states.h"

SDL_Texture *game_over_text = NULL;
SDL_Texture *final_score_text = NULL;
SDL_Texture *reset_text = NULL;

float reset_text_y = 0.0f;
bool reset_text_move_down = false;

float end_delay_timer = 0.0f;
const float END_DELAY_TIME = 0.5f;

void end_init(void) {
	SDL_Surface *tmp_surface = NULL;

	tmp_surface = TTF_RenderText_Solid_Wrapped(title_font, "GAME\nOVER", 0, NOKIA_LIGHT, 0);
	game_over_text = SDL_CreateTextureFromSurface(get_renderer(), tmp_surface);
	SDL_DestroySurface(tmp_surface);

	tmp_surface = TTF_RenderText_Solid(label_font, "Final Score: 00", 0, NOKIA_LIGHT);
	final_score_text = SDL_CreateTextureFromSurface(get_renderer(), tmp_surface);
	SDL_DestroySurface(tmp_surface);

	tmp_surface = TTF_RenderText_Solid_Wrapped(label_font, "PRESS Shoot to\nRESET", 0, NOKIA_LIGHT, 0);
	reset_text = SDL_CreateTextureFromSurface(get_renderer(), tmp_surface);
	SDL_DestroySurface(tmp_surface);

	reset_text_y = 80.0f;
	reset_text_move_down = true;
}

void end_deinit(void) {
	unload_texture(game_over_text);
	unload_texture(final_score_text);
	unload_texture(reset_text);
}

void end_setup(int final_score, bool is_dead) {
	SDL_Surface *tmp_surface = NULL;

	if (is_dead) {
		tmp_surface = TTF_RenderText_Solid_Wrapped(title_font, "YOU DIED", 0, NOKIA_LIGHT, 0);
		game_over_text = SDL_CreateTextureFromSurface(get_renderer(), tmp_surface);
		SDL_DestroySurface(tmp_surface);
	} else {
		tmp_surface = TTF_RenderText_Solid_Wrapped(title_font, "TIME UP", 0, NOKIA_LIGHT, 0);
		game_over_text = SDL_CreateTextureFromSurface(get_renderer(), tmp_surface);
		SDL_DestroySurface(tmp_surface);
	}

	char buffer[32];

	snprintf(buffer, sizeof(buffer), "Final Score: %02d", final_score);

	unload_texture(final_score_text);

	tmp_surface = TTF_RenderText_Solid(label_font, buffer, 0, NOKIA_LIGHT);
	final_score_text = SDL_CreateTextureFromSurface(get_renderer(), tmp_surface);
	SDL_DestroySurface(tmp_surface);

	end_delay_timer = 0.0f;
}

bool end_update(float dt) {
	if ( shoot_key && !shoot_key_held && end_delay_timer > END_DELAY_TIME) {
    shoot_key_held = true;
    return true;
  }

	if (end_delay_timer <= END_DELAY_TIME)
		end_delay_timer += dt;
	
  if (reset_text_move_down) {
    reset_text_y += 2.0f * dt;
    if (reset_text_y > 82.0f)
      reset_text_move_down = false;
  }
  else {
    reset_text_y -= 2.0f * dt;
    if (reset_text_y < 80.0f)
      reset_text_move_down = true;
  }

	return false;
}

void end_draw(void) {
	draw_texture(game_over_text, 8.0f, 40.0f);
	draw_texture(final_score_text, 14.0f, 62.0f);
	draw_texture(reset_text, 8.0f, reset_text_y);
}
