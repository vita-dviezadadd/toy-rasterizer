#pragma once

#include "SDL.h"
#include "SDL_pixels.h"

const int w = 400;
const int h = 400;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;
uint32_t* framebuffer;

void init(const int &w, const int &h, SDL_Window *&window, 
          SDL_Renderer *&renderer, SDL_Texture *&texture,
          uint32_t *&framebuffer);
void process_input(bool &quit);
void render(const int &w, SDL_Renderer *&renderer, SDL_Texture *&texture, uint32_t *&framebuffer);
void deinit(SDL_Window *&window, SDL_Renderer *&renderer, SDL_Texture *&texture, uint32_t *&framebuffer);

void init(const int &w, const int &h, SDL_Window *&window, 
          SDL_Renderer *&renderer, SDL_Texture *&texture,
          uint32_t *&framebuffer) {
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            w, h, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                              SDL_TEXTUREACCESS_STREAMING, w, h);
  framebuffer = new uint32_t[w * h];
}

void process_input(bool &quit) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      quit = true;
    }
  }
}

void render(const int &w, SDL_Renderer *&renderer, SDL_Texture *&texture,
               uint32_t *&framebuffer) {
  SDL_UpdateTexture(texture, nullptr, framebuffer, w * sizeof(uint32_t));
  SDL_RenderCopy(renderer, texture, nullptr, nullptr);
  SDL_RenderPresent(renderer);
}

void deinit(SDL_Window *&window, SDL_Renderer *&renderer, SDL_Texture *&texture, uint32_t *&framebuffer) {
  delete[] framebuffer;
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}