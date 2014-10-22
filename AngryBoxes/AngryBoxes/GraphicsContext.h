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

	void DrawOrientedBoundingBox(const OrientedBoundingBox& box);
	void DrawGameObject(GameObject&);
	void Clear();
	void Update();
	void SwapBuffers();

private:
	sf::RenderWindow window_;
	Texture redTexture;
	sf::Sprite tempSprite_;
};

#endif // GraphicsContext_h__