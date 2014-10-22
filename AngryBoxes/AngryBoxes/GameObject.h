#ifndef GameObject_h__
#define GameObject_h__

#include "PhysicObject.h"
#include "Texture.h"
#include "SFML\Graphics\Sprite.hpp"

class GameObject : public PhysicsObject
{
public:
	GameObject();
	GameObject(std::string);
	GameObject(float, const Vector2&, const OrientedBoundingBox&, std::string);
	
	const sf::Sprite& getSprite();
	void updateGraphics();

private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
};
#endif

