#include "renderer.h"
#include "SDL_image.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height)
    : screen_width(screen_width), screen_height(screen_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

// Clear screen
void Renderer::Clear() {
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
}

//Init
void Renderer::Init(Logic * logic){

  std::string file("data/player_1.png");
  // SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
  // "Loading %s", file);

  SDL_Texture* texture = IMG_LoadTexture(sdl_renderer, file.c_str());
  if (texture == nullptr) {
    std::cout << "IMG_LoadTexture failed: " << SDL_GetError();
  }
  logic->_player1->setTexture(texture);
}

void Renderer::Render(Logic* logic) {
  // SDL_Rect block;
  // block.w = screen_width / grid_width;
  // block.h = screen_height / grid_height;

  // TEST rendering

  SDL_Rect dest = {logic->_player1->getPosX(),logic->_player1->getPosy(),0,0}; 

  // Query size (width and hight from texture)
  SDL_QueryTexture(logic->_player1->getTexture(), NULL, NULL, &dest.w, &dest.h);
  // Render texture with orignal size to dest.x & dest.y
  SDL_RenderCopy(sdl_renderer, logic->_player1->getTexture(), NULL, &dest);

  // Render
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Score: " + std::to_string(score) +
                    " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
