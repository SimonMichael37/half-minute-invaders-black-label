#pragma once

struct SDL_FRect;

struct Player {
  float x;
  float y;
  SDL_FRect hitbox;

  void init(void);
  void reset(void);
  void move(int move_x, float dt);
};

struct Bullet {
  float x;
  float y;
  SDL_FRect hitbox;

  void init(void);
  void reset(void);
  void shoot(float x, float y);
  void move(float dt);
  bool out_of_bounds(void);
};
