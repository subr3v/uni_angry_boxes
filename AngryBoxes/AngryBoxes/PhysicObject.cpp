#include "PhysicObject.h"

PhysicsObject::PhysicsObject() { }

PhysicsObject::PhysicsObject(float mass, const Vector2& position, const OrientedBoundingBox& shape) : m_position(position), m_velocity(Vector2(0,0)), m_mass(mass),
							m_angularVelocity(0) , m_shape(shape), m_rotation(0), m_immovable(false) {

}