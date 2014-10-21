#include "PhysicsSimulation.h"
#include "PhysicObject.h"

PhysicsSimulation::PhysicsSimulation() {

}

PhysicsSimulation::~PhysicsSimulation() {
	// Destroy all the objects.
	for(std::vector<PhysicsObject*>::iterator it = objects.begin(); it != objects.end(); it++) {
		delete (*it);
	}
	objects.clear();
}

PhysicsObject* PhysicsSimulation::createObject(float mass, const Vector2& position, const OrientedBoundingBox& shape) {
	PhysicsObject* object = new PhysicsObject(mass, position, shape);
	objects.push_back(object);
	return object;
}

void PhysicsSimulation::destroyObject(PhysicsObject* object) {
	for(std::vector<PhysicsObject*>::iterator it = objects.begin(); it != objects.end(); it++) {
		if( (*it) == object ) {
			objects.erase(it);
			break;
		}
	}
}

void PhysicsSimulation::step(float dt) {
	// Move Objects

	// Detect collision
	
	// Collision response
}