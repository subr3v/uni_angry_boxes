#include "GameObject.h"
#include <iostream>

#define M_PI 3.14159265358979323846

GameObject::GameObject()
{
	if (!m_texture.loadFromFile("RedBox.png", sf::IntRect(10, 10, shape().width, shape().height)))
	{
		std::cout << "ERROR CAN'T LOAD RedBox.png (GameObject::GameObject())" << std::endl;
	}
	m_texture.setSmooth(true);
	m_sprite.setTexture(m_texture);
}

GameObject::GameObject(std::string filename)
{
	if (!m_texture.loadFromFile(filename, sf::IntRect(10, 10, 32, 32)))
	{
		std::cout << "ERROR CAN'T LOAD " << filename << " (GameObject::GameObject())" << std::endl;
	}
	m_texture.setSmooth(true);
	m_sprite.setTexture(m_texture);
}

GameObject::GameObject(float mass1, const Vector2& position1, const OrientedBoundingBox& shape1, std::string filename)
{
	position(position1);
	velocity(Vector2(0, 0));
	mass(mass1);
	angularVelocity(0);
	shape(shape1);
	rotation(0);
	immovable(false);

	if (!m_texture.loadFromFile(filename, sf::IntRect(10, 10, shape().width, shape().height)))
	{
		std::cout << "ERROR CAN'T LOAD " << filename << " (GameObject::GameObject())" << std::endl;
	}
	m_texture.setSmooth(true);
	m_sprite.setTexture(m_texture);
}

void GameObject::updateGraphics()
{
	m_sprite.setScale(2, 2);
	//m_sprite.setPosition(position().x - (shape().width / 2 * cosf(rotation())), position().y - (shape().height / 2 * sinf(rotation())));
	m_sprite.setPosition(position().x, position().y);
	m_sprite.setRotation(rotation()*180/M_PI);
}

const sf::Sprite& GameObject::getSprite()
{
	return m_sprite;
}