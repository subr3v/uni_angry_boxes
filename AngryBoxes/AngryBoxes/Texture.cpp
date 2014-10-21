#include "Texture.h"
#include <iostream>

Texture::Texture()
{
	if (!texture_.loadFromFile("RedBox.png"))
	{
		// error...
		std::cout << "ERROR! IMAGE FAILED TO LOAD (GraphicsContext::GraphicsContext)" << std::endl;
	}
	texture_.setSmooth(true);
}

sf::Texture Texture::GetTexture()
{
	return texture_;
}