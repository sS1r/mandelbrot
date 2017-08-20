#ifndef SDLTOOLS_HPP
#define SDLTOOLS_HPP

#include <vector>

#include <SDL2/SDL.h>

#include "Window.hpp"

//Initializes SDL2
void initGraphics();

//Quits SDL2
void quitGraphics();

//Wait for ms milliseconds
void wait(unsigned ms);

//Creates new texture from pixels
SDL_Texture* createTexture(const Window& window, std::vector<std::vector<unsigned>> pixels);

#endif
