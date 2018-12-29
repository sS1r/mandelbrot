#ifndef SDLTOOLS_HPP
#define SDLTOOLS_HPP

//Initializes SDL2
void initGraphics();

//Quits SDL2
void quitGraphics();

//Wait for ms milliseconds
void wait(unsigned ms);

//Gets milliseconds from start of SDL2
unsigned getTicks();

#endif
