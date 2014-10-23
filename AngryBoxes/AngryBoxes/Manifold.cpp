#include "Manifold.h"
#include "PhysicObject.h"
#include "PhysicsSimulation.h"
#include <algorithm>

#include "GraphicsContext.h"

void Manifold::solve()
{
	OverlapResult result;
	bool collides = a->shape.Overlaps(b->shape, result);
	contactCount = result.contactCount;
	contactPoints[0] = result.contactPoints[0];
	contactPoints[1] = result.contactPoints[1];

	//normal = -result.normal;
	penetrationAmount = result.penetration;

	if (collides)
	{
		Vector2 normal1 = a->position - contactPoints[0];
		Vector2 normal2 = a->position - contactPoints[1];
		normal = (normal1 + normal2) * 0.5f;
		normal = a->position - (contactPoints[0] + contactPoints[1]) * 0.5f;
		normal.normalize();

		context->DrawLine(contactPoints[0], contactPoints[0] + normal * penetrationAmount * 50, sf::Color::Yellow);
		//a->position += normal * penetrationAmount;
	}
}

void Manifold::init(float dt)
{
	// Calculate average restitution
	restitution = std::min( a->restitution, b->restitution );

	// Calculate static and dynamic friction
	staticFriction = std::sqrt( a->staticFriction * a->staticFriction );
	dynamicFriction = std::sqrt( a->dynamicFriction * a->dynamicFriction );

	for(int i = 0; i < contactCount; ++i)
	{
		// Calculate radii from COM to contact
		Vector2 ra = contactPoints[i] - a->position;
		Vector2 rb = contactPoints[i] - b->position;

		Vector2 rv = b->velocity + cross(b->angularVelocity, rb) - a->velocity - cross(a->angularVelocity, ra);

		// Determine if we should perform a resting collision or not
		// The idea is if the only thing moving this object is gravity,
		// then the collision should be performed without any restitution
		if(rv.LengthSquared() < (simulation->gravity() * dt).LengthSquared() + EPSILON)
			restitution = 0.0f;
	}
}

void Manifold::applyImpulse()
{
	// Early out and positional correct if both objects have infinite mass
	if( fequals(a->inverseMass, 0) && fequals(b->inverseMass, 0))
	{
		solveInfiniteMass();
		return;
	}

	for(int i = 0; i < contactCount; ++i)
	{
		// Calculate radii from COM to contact
		Vector2 ra = contactPoints[i] - a->position;
		Vector2 rb = contactPoints[i] - b->position;

		Vector2 rv = b->velocity + cross(b->angularVelocity, rb) - a->velocity - cross(a->angularVelocity, ra);

		// Relative velocity along the normal
		float contactVel = -rv.dot(normal);

		// Do not resolve if velocities are separating
		if (contactVel > 0)
			return;

		float raCrossN = cross(ra, normal);
		float rbCrossN = cross(rb, normal);
		float inverseMassSum = a->inverseMass + b->inverseMass;// + (sqrt(raCrossN) * a->inverseInertia) + (sqrt(rbCrossN) * b->inverseInertia);

		// Calculate impulse scalar
		float j = -(1.0f + restitution) * contactVel;
		j /= inverseMassSum;
		j /= (float)contactCount;

		// Apply impulse
		Vector2 impulse = -normal * j;
		a->applyImpulse(-impulse, ra);
		b->applyImpulse( impulse, rb);

		// Friction impulse
		rv = b->velocity + cross(b->angularVelocity, rb) -
			a->velocity - cross(a->angularVelocity, ra);

		Vector2 t = rv - (normal * rv.dot(normal));
		t.normalize();

		// j tangent magnitude
		float jt = -rv.dot(t);
		jt /= inverseMassSum;
		jt /= (float)contactCount;

		// Don't apply tiny friction impulses
		if (fequals(jt, 0.0f))
			return;

		// Coulumb's law
		Vector2 tangentImpulse;
		if(std::abs(jt) < j * staticFriction)
			tangentImpulse = t * jt;
		else
			tangentImpulse = t * -j * dynamicFriction;

		// Apply friction impulse
		a->applyImpulse(-tangentImpulse, ra);
		b->applyImpulse(tangentImpulse, rb);
	}
}

void Manifold::solvePosition()
{
	if( a->mass == 0 )
		return;
	const float kThreshold = 0.05f; // Threshold
	const float percent = 0.01f; // Penetration percentage to correct
	Vector2 correction = -normal * (std::max( penetrationAmount - kThreshold, 0.0f ) / (a->inverseMass + b->inverseMass)) * percent;
	//Vector2 correction = -normal * penetrationAmount * percent; // (std::max( penetrationAmount - kThreshold, 0.0f ) / (a->inverseMass + b->inverseMass)) * percent;
	a->position -= correction * a->inverseMass;
	b->position += correction * b->inverseMass;
}

void Manifold::solveInfiniteMass()
{
	a->velocity = Vector2(0, 0);
	b->velocity = Vector2(0, 0);
}
