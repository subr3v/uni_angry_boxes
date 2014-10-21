#include "GraphicsContext.h"
#include "Texture.h"

GraphicsContext::GraphicsContext() : window_(sf::VideoMode(800, 600), "Angry Boxes")
{
	tempSprite_.setTexture(redTexture.GetTexture());
}

void GraphicsContext::Update()
{
	// run the program as long as the window is open
	while (window_.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window_.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window_.close();
		}

		// clear the window with black color
		window_.clear(sf::Color::Black);

		// draw everything here...
		// window.draw(...);
		window_.draw(tempSprite_);

		// end the current frame
		window_.display();
	}
}