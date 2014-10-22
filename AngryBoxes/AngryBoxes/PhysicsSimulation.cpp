#include "PhysicsSimulation.h"
#include "PhysicObject.h"

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
	// Move Objects

	for(std::vector<PhysicsObject*>::iterator it = m_objects.begin(); it != m_objects.end(); it++) {
		PhysicsObject* obj = *it;

		PhysicsObject nextState = *obj;

		if (obj->immovable() == false)
		{
			obj->m_velocity += m_gravity * dt;
			obj->m_angularVelocity *= 0.1;

			obj->m_rotation += nextState.m_angularVelocity * dt;
			obj->m_shape.UpdateOBB2D(nextState.position(), nextState.rotation());
			collisionCheckAndRespond(obj);

			obj->m_position.y += nextState.m_velocity.y * dt;
			obj->m_shape.UpdateOBB2D(nextState.position(), nextState.rotation());
			collisionCheckAndRespond(obj);

			obj->m_position.x += nextState.m_velocity.x * dt;
			obj->m_shape.UpdateOBB2D(nextState.position(), nextState.rotation());
			collisionCheckAndRespond(obj);
		}

		obj->m_shape.UpdateOBB2D(nextState.position(), nextState.rotation());
	}

	// Detect collision
	
	// Collision response
}

void PhysicsSimulation::collisionCheckAndRespond(PhysicsObject* obj)
{
	PhysicsObject& myObject = *obj;
	for(std::vector<PhysicsObject*>::iterator it = m_objects.begin(); it != m_objects.end(); it++) 
	{
		PhysicsObject* collider = *it;
		if( collider == obj )
			continue;

		OverlapResult result;
		if (myObject.m_shape.Overlaps(collider->shape(), result)) {
			
			for ( int i = 0; i < 2; i++ )
			{
				float correction = result.amount[i];
				Vector2 offset = myObject.m_shape.axis[i] * correction * 2;
				myObject.position(myObject.position() - offset);
			}

			//myObject.velocity(Vector2(0,0));
			//nextState.angularVelocity(angularVel);
		}
	}
}