#include "mylib.h"

#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "SDL3_mixer/SDL_mixer.h"

struct Core {
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  bool window_should_close = true;
	MIX_Mixer *mixer = nullptr;
};

static Core core;

/* ----------------------- */
/* ------ Functions ------ */
/* ----------------------- */

void init_window(const char *title, int width, int height) {
  SDL_InitFlags sdl_flags = (SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  SDL_Init(sdl_flags);

  TTF_Init();

	MIX_Init();

  SDL_WindowFlags win_flags = 0;
  core.window = SDL_CreateWindow(title, width, height, win_flags);
  SDL_SetWindowPosition(core.window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

  core.window_should_close = false;

  core.renderer = SDL_CreateRenderer(core.window, nullptr);

	core.mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
}

void close_window(void) {
  SDL_DestroyRenderer(core.renderer);
  SDL_DestroyWindow(core.window);

  TTF_Quit();

  SDL_Quit();
}

/* ------ Line Break ------ */

SDL_Window *get_window(void) {
  return core.window;
}

SDL_Renderer *get_renderer(void) {
  return core.renderer;
}

MIX_Mixer *get_mixer(void) {
	return core.mixer;
}

/* ------ Line Break ------ */

bool window_should_close(void) {
  return core.window_should_close;
}

int get_window_width(void) {
  int width = 0;
  SDL_GetWindowSize(core.window, &width, NULL);

  return width;
}

int get_window_height(void) {
  int height = 0;
  SDL_GetWindowSize(core.window, NULL, &height);

  return height;
}

int get_logical_width(void) {
  int width = 0;
  SDL_GetRenderLogicalPresentation(core.renderer, &width, NULL, NULL);

  return width;
}

int get_logical_height(void) {
  int height = 0;
  SDL_GetRenderLogicalPresentation(core.renderer, NULL, &height, NULL);

  return height;
}

/* ------ Line Break ------ */

void set_logical_size(int width, int height) {
  SDL_SetRenderLogicalPresentation(core.renderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
  SDL_SetDefaultTextureScaleMode(core.renderer, SDL_SCALEMODE_PIXELART);
}

void set_window_should_close(bool state) {
  core.window_should_close = state;
}
