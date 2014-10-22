#include "GraphicsContext.h"
#include "Texture.h"

GraphicsContext::GraphicsContext() : window_(sf::VideoMode(800, 600), "Angry Boxes")
{
	tempSprite_.setTexture(redTexture.GetTexture());
}

void GraphicsContext::DrawOrientedBoundingBox(const OrientedBoundingBox& box)
{
	sf::ConvexShape polygon;
	polygon.setPointCount(4);
	for(int i = 0; i < 4; i++)
		polygon.setPoint(i, sf::Vector2f(box.corner[i].x, box.corner[i].y));
	polygon.setOutlineColor(sf::Color::White);
	polygon.setFillColor(sf::Color::Transparent);
	polygon.setOutlineThickness(1);
	window_.draw(polygon);
}

void GraphicsContext::SwapBuffers()
{
	window_.display();
}

void GraphicsContext::Clear()
{
	window_.clear(sf::Color::Black);
}

void GraphicsContext::Update()
{
	// run the program as long as the window is open
	if (window_.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		if (window_.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window_.close();
		}

		// clear the window with black color

		// draw everything here...
		// window.draw(...);
		//window_.draw(tempSprite_);

		// end the current frame
	}
}