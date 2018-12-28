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

	int getDragX();
	int getDragY();
	
	bool increaseIters();
	bool decreaseIters();
	
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

	//Iteration count management
	bool _increaseIters;
	bool _decreaseIters;

	//Mouse left button state
	bool mousePressed;

	//Tells if mouse left button was released
	bool mouseReleased;

	//Quit event state
	bool quit;
};
 
#endif
