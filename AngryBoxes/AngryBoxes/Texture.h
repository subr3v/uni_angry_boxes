#ifndef Texture_h__
#define Texture_h__

#include "SFML\Graphics\Texture.hpp"

class Texture
{
protected:
	sf::Texture texture_;
	int x_;
	int y_;
	int width_;
	int height_;

public:
	Texture();
	void Update();
	sf::Texture GetTexture();
};

#endif // Texture_h__
