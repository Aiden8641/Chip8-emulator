#ifndef PLATFORM
#define PLATFORM
#include "chip8.h"
#include <SDL3/SDL.h>
#include <string_view>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 320;

class Platform {
public:
  // int textureWidth, int textureHeight
  Platform(std::string_view title);
  ~Platform();

  void update(void const *buffer, int pitch);
  void processInput(Chip8 &chip8);

private:
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  SDL_Texture *texture = nullptr;
  const bool *key_states = SDL_GetKeyboardState(NULL);
};

#endif // !PLATFORM
