#include "GraphicsContext.h"

int main()
{
    // create the window
    //sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	GraphicsContext graphicsContext;

	while (true)
	{
		graphicsContext.Update();
	}

    return 0;
}