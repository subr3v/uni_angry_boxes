#include "InputManager.h"


void InputManager::init(sf::Window* applicationPointer)
{
	windowPointer = applicationPointer;
}

//main input loop to process all inputs.
void InputManager::getInput()
{
	while(windowPointer->pollEvent(EventManager))
	{
		switch(EventManager.type)
		{
			//Close window when requested
			case sf::Event::Closed:
			{
				windowPointer->close();
				break;
			}

			//Updates mouse position
			case sf::Event::MouseMoved :
			{
				currentXPos = EventManager.mouseMove.x;
				currentYPos = EventManager.mouseMove.y;
				break;
			}
			
			//Takes down drag start location when left click
			case sf::Event::MouseButtonPressed :
			{
				if(EventManager.mouseButton.button == sf::Mouse::Left)
				{
					xDragStart = EventManager.mouseButton.x;
					yDragStart = EventManager.mouseButton.y;
				}

				break;
			}

			
			case sf::Event::MouseButtonReleased :
			{
				if(EventManager.mouseButton.button == sf::Mouse::Left)
				{
					releaseBox = true;
					xDragEnd = EventManager.mouseButton.x;
					yDragEnd = EventManager.mouseButton.y;
				}

				break;
			}

			case sf::Keyboard::Escape :
			{
				windowPointer->close();
			}
		}
	}
}


//Get funtions to return appropriate variable
bool InputManager::getReleaseBox()
{
	return releaseBox;
}

void InputManager::setReleaseBox(bool newReleaseBox)
{
	releaseBox = newReleaseBox;
}

int InputManager::getXDragStart()
{
	return xDragStart;
}

int InputManager::getYDragStart()
{
	return yDragStart;
}

int InputManager::getXDragEnd()
{
	return xDragEnd;
}

int InputManager::getYDragEnd()
{
	return yDragEnd;
}

int InputManager::getCurrentXPos()
{
	return currentXPos;
}

int InputManager::getCurrentYPos()
{
	return currentYPos;
}