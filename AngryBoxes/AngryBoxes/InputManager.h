#ifndef InputManager_h__
#define InputManager_h__

#include <SFML/Window.hpp>




class InputManager
{



public:

	void init(sf::Window*);
	void getInput();
	bool getReleaseBox();
	void setReleaseBox(bool);
	int getXDragStart();
	int getYDragStart();
	int getXDragEnd();
	int getYDragEnd();
	int getCurrentXPos();
	int getCurrentYPos();

protected:

	bool releaseBox;

	//instance of event class which stores event
	sf::Event EventManager; 
	sf::Window* windowPointer;
	
	int currentXPos, currentYPos;
	int xDragStart, yDragStart, xDragEnd, yDragEnd;



};


#endif // InputManager_h__
