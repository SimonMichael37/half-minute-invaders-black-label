#pragma once

struct SDL_Texture;
struct SDL_Color;
struct TTF_Font;

const SDL_Color NOKIA_DARK = { 67, 82, 61, 255 };
const SDL_Color NOKIA_LIGHT = { 199, 240, 216, 255 };

extern SDL_Texture *player_texture;
extern SDL_Texture *bullet_texture;
extern SDL_Texture *enemy_texture;
extern SDL_Texture *explosion_texture;

extern TTF_Font *title_font;
extern TTF_Font *subtitle_font;
extern TTF_Font *label_font;

extern MIX_Audio *laser_sound;
extern MIX_Audio *enemy_hit_sound;
extern MIX_Audio *victory_jingle;
extern MIX_Audio *player_hit_sound;

extern bool left_key;
extern bool right_key;
extern bool shoot_key;
extern bool shoot_key_held;

extern int MAX_DURATION;
extern int duration_left;

extern float DURATION_TIME;
extern float duration_timer;

extern int score;
