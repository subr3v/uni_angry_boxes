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

	const std::vector<PhysicsObject*>& getObjects() { return m_objects; }

	inline void gravity(const Vector2& gravity) { m_gravity = gravity; }
	inline const Vector2 gravity() const { return m_gravity; }
private:
	void collisionCheckAndRespond(PhysicsObject* obj);

	std::vector<PhysicsObject*> m_objects;
	Vector2 m_gravity;
};

#endif // PhysicsSimulation_h__
