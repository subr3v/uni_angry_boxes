#include "GameObject.h"
#include <iostream>

#define M_PI 3.14159265358979323846

GameObject::GameObject(PhysicsObject* object, std::string filename) : object(object)
{
	if (!m_texture.loadFromFile(filename, sf::IntRect(10, 10, object->shape().width, object->shape().height)))
	{
		std::cout << "ERROR CAN'T LOAD RedBox.png (GameObject::GameObject())" << std::endl;
	}
	m_texture.setSmooth(true);
	m_sprite.setTexture(m_texture);
}

void GameObject::updateGraphics()
{
	m_sprite.setScale(2, 2);
	//m_sprite.setPosition(position().x - (shape().width / 2 * cosf(rotation())), position().y - (shape().height / 2 * sinf(rotation())));
	m_sprite.setPosition(object->position().x, object->position().y);
	m_sprite.setRotation(object->rotation()*180/M_PI);
}

const sf::Sprite& GameObject::getSprite()
{
	return m_sprite;
}