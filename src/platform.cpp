#include "platform.h"
#include "chip8.h"
// #include <SDL3/SDL.h>
#include <array>
#include <cstddef>
#include <string_view>

Platform::Platform(std::string_view title) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Failed to init SDL: %s", SDL_GetError());
  }

  if (!SDL_CreateWindowAndRenderer(title.data(), WINDOW_WIDTH, WINDOW_HEIGHT,
                                   SDL_WINDOW_RESIZABLE, &window, &renderer)) {
    SDL_Log("Failed to create window/renderer: %s", SDL_GetError());
  }

  // texture must be 64 x 32 because chip8 is for 64 x 32 screen
  texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_STREAMING, VIDEO_WIDTH, VIDEO_HEIGHT);
}

Platform::~Platform() {
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Platform::update(const std::array<uint32_t, 64 * 32> buffer, int pitch) {
  // sdl scales the texture to the rect
  const SDL_FRect dstrect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

  SDL_UpdateTexture(texture, nullptr, buffer.data(), pitch);
  SDL_RenderClear(renderer);
  SDL_RenderTexture(renderer, texture, nullptr, &dstrect);
  SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
  SDL_RenderPresent(renderer);
}

void Platform::processInput(Chip8 &chip8) {
  // keys: 1 2 3 4
  chip8.setKey(1, key_states[SDL_SCANCODE_1]);
  chip8.setKey(2, key_states[SDL_SCANCODE_2]);
  chip8.setKey(3, key_states[SDL_SCANCODE_3]);
  chip8.setKey(0xC, key_states[SDL_SCANCODE_4]);

  // keys: q w e r
  chip8.setKey(4, key_states[SDL_SCANCODE_Q]);
  chip8.setKey(5, key_states[SDL_SCANCODE_W]);
  chip8.setKey(6, key_states[SDL_SCANCODE_E]);
  chip8.setKey(0xD, key_states[SDL_SCANCODE_R]);

  // keys: a s d f
  chip8.setKey(7, key_states[SDL_SCANCODE_A]);
  chip8.setKey(8, key_states[SDL_SCANCODE_S]);
  chip8.setKey(9, key_states[SDL_SCANCODE_D]);
  chip8.setKey(0xE, key_states[SDL_SCANCODE_F]);

  // keys: z x c v
  chip8.setKey(0xA, key_states[SDL_SCANCODE_Z]);
  chip8.setKey(0, key_states[SDL_SCANCODE_X]);
  chip8.setKey(0xB, key_states[SDL_SCANCODE_C]);
  chip8.setKey(0xF, key_states[SDL_SCANCODE_V]);
}
