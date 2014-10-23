#ifndef GameObject_h__
#define GameObject_h__

#include "PhysicObject.h"
#include "Texture.h"
#include "SFML\Graphics\Sprite.hpp"

class GameObject
{
public:
	GameObject(PhysicsObject* object, std::string);
	
	const sf::Sprite& getSprite();
	void updateGraphics();

private:
	PhysicsObject* object;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
};
#endif

