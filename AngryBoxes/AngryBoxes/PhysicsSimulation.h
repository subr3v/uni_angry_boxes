#ifndef PhysicsSimulation_h__
#define PhysicsSimulation_h__

#include "Vector2.h"
#include "OrientedBoundingBox.h"
#include <vector>

class PhysicsObject;

class PhysicsSimulation {
public:
	PhysicsSimulation();
	~PhysicsSimulation();

	PhysicsObject* createObject(float mass, const Vector2& position, const OrientedBoundingBox& shape);
	void destroyObject(PhysicsObject* object);
	void step(float dt);
private:
	std::vector<PhysicsObject*> objects;
};

#endif // PhysicsSimulation_h__
