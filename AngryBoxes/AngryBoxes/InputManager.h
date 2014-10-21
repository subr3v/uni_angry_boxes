#ifndef InputManager_h__
#define InputManager_h__

#include <SFML/Window.hpp>


class InputManager
{

public:

	void init(sf::Window*);
	void getInput();

protected:

	void releaseBox(int, int);

	//instance of event class which stores event
	sf::Event EventManager; 
	sf::Window* windowPointer;
	
	int currentXPos, currentYPos;
	int xDragStart, yDragStart;



};


#endif // InputManager_h__
