#ifndef PLATFORM
#define PLATFORM
#include "chip8.h"
#include <SDL3/SDL.h>
#include <array>
#include <string_view>

constexpr int WINDOW_WIDTH = 640;
constexpr int WINDOW_HEIGHT = 320;

class Platform {
public:
  // int textureWidth, int textureHeight
  Platform(std::string_view title);
  ~Platform();

  void update(const std::array<uint32_t, 64 * 32> buffer, int pitch);
  void processInput(Chip8 &chip8);

private:
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  SDL_Texture *texture = nullptr;
  const bool *key_states = SDL_GetKeyboardState(NULL);
};
#endif // !PLATFORM
