#include "PhysicsSimulation.h"
#include "PhysicObject.h"

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
	// Move Objects

	// Detect collision
	
	// Collision response
}