#include "GraphicsContext.h"
#include "Texture.h"

#define M_PI 3.14159265358979323846

GraphicsContext *context;

GraphicsContext::GraphicsContext() : window_(sf::VideoMode(800, 600), "Angry Boxes")
{
	context = this;
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
	polygon.setOutlineThickness(-1);

	for(int i = 0; i < 2; i++)
	{
		float len = i == 0 ? box.width : box.height;
		sf::RectangleShape axis(sf::Vector2f(box.origin[i] * 100, 1));
		axis.setPosition(sf::Vector2f(box.center.x , box.center.y));
		float rotation = atan2(box.axis[i].y, box.axis[i].x);
		axis.setRotation(rotation * 180 / M_PI);

		//window_.draw(axis);
		/*
		if(  box.overlapInfo[i].overlaps )
		{
			sf::RectangleShape correction(sf::Vector2f(box.overlapInfo[i].amount, 1));
			correction.setPosition(sf::Vector2f(box.corner[0].x, box.corner[0].y));
			correction.setRotation(rotation * 180 / M_PI);
			correction.setFillColor(sf::Color::Blue);

			window_.draw(correction);
		}*/
	}

	window_.draw(polygon);
}

void GraphicsContext::DrawGameObject(GameObject& object)
{
	object.updateGraphics();
	window_.draw(object.getSprite());
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

void GraphicsContext::DrawLine( const Vector2& start, const Vector2& end, const sf::Color color)
{
	Vector2 edge = end - start;
	sf::RectangleShape line(sf::Vector2f(edge.getLength(), 1));
	line.setPosition(start.x, start.y);
	line.setRotation(atan2(edge.y, edge.x) * 180 / PI);
	line.setFillColor(color);

	window_.draw(line);
}

void GraphicsContext::DrawPoint( const Vector2& pt, const sf::Color color /*= sf::Color(0, 0, 255)*/ )
{
	sf::RectangleShape point(sf::Vector2f(5, 5));
	point.setPosition(pt.x, pt.y);
	point.setFillColor(color);
	window_.draw(point);
}
