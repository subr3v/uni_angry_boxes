#ifndef GraphicsContext_h__
#define GraphicsContext_h__

#include <SFML/Graphics.hpp>
#include "Texture.h"
#include "OrientedBoundingBox.h"
#include "GameObject.h"

class GraphicsContext
{
public:
	GraphicsContext();

	void DrawLine(const Vector2& start, const Vector2& end, const sf::Color color = sf::Color(0, 0, 255));
	void DrawPoint(const Vector2& pt, const sf::Color color = sf::Color(0, 0, 255));
	void DrawOrientedBoundingBox(const OrientedBoundingBox& box);
	void DrawGameObject(GameObject&);
	void Clear();
	void Update();
	void SwapBuffers();

	sf::Window* getWindow() { return &window_; }

private:
	sf::RenderWindow window_;
	Texture redTexture;
	sf::Sprite tempSprite_;
};

extern GraphicsContext* context;

#endif // GraphicsContext_h__