#include "PhysicObject.h"

PhysicsObject::PhysicsObject() { }

PhysicsObject::PhysicsObject(float mass, const Vector2& position, const OrientedBoundingBox& shape) :
		position(position), force(Vector2(0, 0)), velocity(Vector2(0, 0)), shape(shape), mass(mass), angularVelocity(0), rotation(0), inertia(0),
		restitution(0.0f), torque(0), staticFriction(1), dynamicFriction(1)
{
	if( mass == 0)
		inverseMass = 0;
	else
		inverseMass = 1 / mass;

	if( inertia == 0)
		inverseInertia = 0;
	else
		inverseInertia = 1 / inertia;

	this->shape.UpdateOBB2D(position, rotation);
}