#ifndef GameObject_h__
#define GameObject_h__

#include "PhysicObject.h"
#include "Texture.h"
#include "SFML\Graphics\Sprite.hpp"

class GameObject : public PhysicsObject
{
public:
	void Update();

private:

	sf::Sprite m_sprite;
	sf::Texture m_texture
};

#endif

