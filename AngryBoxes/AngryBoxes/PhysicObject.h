#ifndef PhysicObject_h__
#define PhysicObject_h__

#include "Vector2.h"
#include "OrientedBoundingBox.h"

class PhysicsSimulation;

class PhysicsObject {
public:
	PhysicsObject(float mass, const Vector2& position, const OrientedBoundingBox& shape);
	PhysicsObject();

	void applyImpulse( const Vector2& impulse, const Vector2& contactVector )
	{
		velocity += impulse * inverseMass;
		angularVelocity += /*inverseInertia * */ cross(contactVector, impulse) * 0.001f;
	}

	float restitution;
	float staticFriction, dynamicFriction;
	float inertia;

	Vector2 position, velocity, force;
	float angularVelocity;
	float torque;
	float mass, inverseMass, inverseInertia;
	float rotation;
	OrientedBoundingBox shape;
};

#endif // PhysicObject_h__
