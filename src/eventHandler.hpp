#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

#include <SDL2/SDL.h>

//Class for event handling
class eventHandler
{
public:
	eventHandler();
	~eventHandler();

	void update();

	int getMouseX();
	int getMouseY();

	int getDragSquareX();
	int getDragSquareY();

	int getDragX();
	int getDragY();

	bool getMousePressed();
	bool getMouseReleased();

	bool getQuit();
private:

	//Current mouse position
	int mouseX;
	int mouseY;

	//Original click position when "dragging" with left click
	int dragX;
	int dragY;

	//Mouse left button state
	bool mousePressed;

	//Tells if mouse left button was released
	bool mouseReleased;

	//Quit event state
	bool quit;
};

#endif
