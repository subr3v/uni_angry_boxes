#include "PhysicsSimulation.h"
#include "PhysicObject.h"
#include "GraphicsContext.h"

#define M_PI 3.14159265358979323846

PhysicsSimulation::PhysicsSimulation() : m_gravity(Vector2(0,0)) {

}

PhysicsSimulation::~PhysicsSimulation() {
	// Destroy all the objects.
	for(std::vector<PhysicsObject*>::iterator it = m_objects.begin(); it != m_objects.end(); it++) {
		delete (*it);
	}
	m_objects.clear();
}

PhysicsObject* PhysicsSimulation::createObject(float mass, const Vector2& position, const OrientedBoundingBox& shape) {
	PhysicsObject* object = new PhysicsObject(mass, position, shape);
	m_objects.push_back(object);
	return object;
}

void PhysicsSimulation::destroyObject(PhysicsObject* object) {
	for(std::vector<PhysicsObject*>::iterator it = m_objects.begin(); it != m_objects.end(); it++) {
		if( (*it) == object ) {
			m_objects.erase(it);
			break;
		}
	}
}

void PhysicsSimulation::step(float dt) {

	contacts.clear();

	// Generate collision info.
	for(int i = 0; i < m_objects.size(); ++i)
	{
		PhysicsObject *a = m_objects[i];

		for(int j = 0; j < m_objects.size(); ++j)
		{
			if( j == i)
				continue;

			PhysicsObject *b = m_objects[j];

			if( a->inverseMass == 0 && b->inverseMass == 0)
				continue;

			Manifold m(this, a, b);
			m.solve();

			if(m.contactCount > 0)
				contacts.emplace_back(m);
		}
	}

	// Integrate forces
	for(std::vector<PhysicsObject*>::iterator it = m_objects.begin(); it != m_objects.end(); it++) {
		integrateForce((*it), dt);
	}

	// Initialise collision
	for(int i = 0; i < contacts.size( ); ++i)
		contacts[i].init(dt);

	const int kIterationNumber = 16;
	// Solve collision
	for(int j = 0; j < kIterationNumber; ++j)
		for(int i = 0; i < contacts.size( ); ++i)
			contacts[i].applyImpulse();

	// Integrate velocities
	for(std::vector<PhysicsObject*>::iterator it = m_objects.begin(); it != m_objects.end(); it++) {
		integrateVelocity((*it), dt);
	}

	// Correct positions
	for(int i = 0; i < contacts.size( ); ++i)
		contacts[i].solvePosition();

	// Clear forces
	for(std::vector<PhysicsObject*>::iterator it = m_objects.begin(); it != m_objects.end(); it++) {
		(*it)->force = Vector2(0, 0);
		(*it)->torque = 0;
	}
}

void PhysicsSimulation::integrateForce( PhysicsObject* object, float dt )
{
	if (object->mass != 0)
	{
		// We divide dt by a half because we're integrating forces before and after collision every frame.
		object->velocity += (object->force * object->inverseMass + m_gravity) * dt * 0.5f;
		object->angularVelocity += object->torque * object->inverseInertia * dt * 0.5f;
		context->DrawLine(object->position, object->position + object->force * 150, sf::Color::Red);
	}
}

void PhysicsSimulation::integrateVelocity( PhysicsObject* object, float dt )
{
	if (object->mass != 0)
	{
		if (object->velocity.getLength() < 0.02f )
			object->velocity = Vector2(0, 0);

		object->position += object->velocity * dt;
		//object->rotation += object->angularVelocity * dt;

		context->DrawLine(object->position, object->position + object->velocity);

		integrateForce(object, dt);
	}
	object->shape.UpdateOBB2D(object->position, object->rotation);
}
