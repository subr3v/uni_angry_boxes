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

	for(std::vector<PhysicsObject*>::iterator it = m_objects.begin(); it != m_objects.end(); it++) {
		PhysicsObject* obj = *it;

		if (obj->immovable() == false)
		{
			obj->m_velocity += m_gravity * dt;
			obj->m_position += obj->m_velocity * dt;
			obj->m_rotation += obj->m_angularVelocity * dt;
		}

		obj->m_shape.UpdateOBB2D(obj->position(), obj->rotation());
	}

	for(std::vector<PhysicsObject*>::iterator it = m_objects.begin(); it != m_objects.end(); it++) {
		PhysicsObject* object = *it;
		for(std::vector<PhysicsObject*>::iterator otherIt = it + 1; otherIt != m_objects.end(); otherIt++) {
			PhysicsObject* collider = *otherIt;

			if (object->shape().Overlaps(collider->shape())) {
				object->velocity(Vector2(0,0));
				object->angularVelocity(0);
			}
		}
	}

	// Detect collision
	
	// Collision response
}