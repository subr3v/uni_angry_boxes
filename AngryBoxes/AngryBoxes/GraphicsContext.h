#ifndef GraphicsContext_h__
#define GraphicsContext_h__

#include <SFML/Graphics.hpp>
#include "Texture.h"

class GraphicsContext
{
public:
	GraphicsContext();
	void Update();

private:
	sf::RenderWindow window_;
	Texture redTexture;
	sf::Sprite tempSprite_;
};

#endif // GraphicsContext_h__