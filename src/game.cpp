#include <cstdlib>
#include <iostream>

#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"

#include "mylib.h"

#include "game.h"
#include "states.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

enum GameState {
  TITLE,
  GAMEPLAY,
  END
};

SDL_Texture *player_texture = NULL;
SDL_Texture *bullet_texture = NULL;
SDL_Texture *enemy_texture = NULL;
SDL_Texture *explosion_texture = NULL;

TTF_Font* title_font = NULL;
TTF_Font* subtitle_font = NULL;
TTF_Font* label_font = NULL;

MIX_Audio *laser_sound = NULL;
MIX_Audio *enemy_hit_sound = NULL;
MIX_Audio *victory_jingle = NULL;
MIX_Audio *player_hit_sound = NULL;
MIX_Audio *start_sound = NULL;

bool left_key = false;
bool right_key = false;
bool shoot_key = false;
bool shoot_key_held = false;

bool state_changed = false;

GameState current_state = TITLE;

int MAX_DURATION = 30;
int duration_left = 0;

float DURATION_TIME = 1.0f;
float duration_timer = 0.0f;

int score = 0;

void load_assets(void) {
  player_texture = load_texture_color_keyed("assets/ship.png", BLACK);
  bullet_texture = load_texture("assets/bullet.png");
  enemy_texture = load_texture_color_keyed("assets/invader.png", BLACK);
  explosion_texture = load_texture_color_keyed("assets/explosion.png", BLACK);

  title_font = TTF_OpenFont("assets/QuinqueFive.ttf", 8.0f);
  TTF_SetFontStyle(title_font, TTF_STYLE_BOLD);

  subtitle_font = TTF_OpenFont("assets/QuinqueFive.ttf", 5.0f);
  TTF_SetFontStyle(subtitle_font, TTF_STYLE_BOLD);

  label_font = TTF_OpenFont("assets/QuinqueFive.ttf", 5.0f);

	laser_sound = load_sound("assets/laser.ogg");
	enemy_hit_sound = load_sound("assets/enemy_hit.ogg");
	victory_jingle = load_sound("assets/victory-c.ogg");
	player_hit_sound = load_sound("assets/player_hit.ogg");
	start_sound = load_sound("assets/select.ogg");
}

void unload_assets(void) {
	unload_texture(player_texture);
	unload_texture(bullet_texture);
	unload_texture(enemy_texture);
	unload_texture(explosion_texture);

	TTF_CloseFont(title_font);
	TTF_CloseFont(subtitle_font);
	TTF_CloseFont(label_font);

	unload_sound(laser_sound);
	unload_sound(enemy_hit_sound);
	unload_sound(victory_jingle);
	unload_sound(player_hit_sound);
	unload_sound(start_sound);
}

void game_init(void) {
  init_window("Half-Minute Invaders - BLACK LABEL", 480, 480);
  set_logical_size(128, 128);

  load_assets();
   
  init_clock(60);

  gameplay_init();
  title_init();
	end_init();

  current_state = TITLE;
}

void handle_key_down(SDL_Keycode key) {
  switch (key) {
    case SDLK_LEFT:
      left_key = true;
      break;
    case SDLK_RIGHT:
      right_key = true;
      break;
    case SDLK_SPACE:
      shoot_key = true;
      break;
  }
}

void handle_key_up(SDL_Keycode key) {
  switch (key) {
    case SDLK_LEFT:
      left_key = false;
      break;
    case SDLK_RIGHT:
      right_key = false;
      break;
    case SDLK_SPACE:
      shoot_key = false;
      shoot_key_held = false;
      break;
  }
}

void handle_events(SDL_Event event) {
  while ( SDL_PollEvent(&event) ) {
    switch (event.type) {
      case SDL_EVENT_QUIT:
        set_window_should_close(true);
        break;
      case SDL_EVENT_KEY_DOWN:
        handle_key_down(event.key.key);
        break;
      case SDL_EVENT_KEY_UP:
        handle_key_up(event.key.key);
        break;
    }
  }
}

void update(float dt) {
  if (current_state == TITLE) {
    state_changed = title_update(dt);

    if (state_changed) {
      duration_timer = 0.0f;

      duration_left = MAX_DURATION;
      update_duration_text(duration_left);

      score = 0;
      update_score_text(score);

      current_state = GAMEPLAY;
			play_sound(start_sound);

      state_changed = false;
    }
  } else if (current_state == GAMEPLAY) {
    state_changed = gameplay_update(dt);
		
    if (state_changed) {
      current_state = END;
      state_changed = false;
    }
  } else if (current_state == END) {
		state_changed = end_update(dt);

		if (state_changed) {
			title_setup();
			current_state = TITLE;
			play_sound(start_sound);
			state_changed = false;
		}
	}
}

void draw(void) {
  clear_screen(NOKIA_DARK);

  if (current_state == TITLE) {
    title_draw();
  } else if (current_state == GAMEPLAY) {
    gameplay_draw();
  } else if (current_state == END) {
		end_draw();
	}

  display_screen();
}

void game_close(void) {
#ifdef __EMSCRIPTEN__
	emscripten_cancel_main_loop();
#endif

	title_deinit();
	gameplay_deinit();
	end_deinit();

	unload_assets();

  close_window();

  exit(0);
}
