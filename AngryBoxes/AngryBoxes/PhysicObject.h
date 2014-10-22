#ifndef PhysicObject_h__
#define PhysicObject_h__

#include "Vector2.h"
#include "OrientedBoundingBox.h"

class PhysicsSimulation;

class PhysicsObject {
public:

	inline const Vector2& position() const { return m_position; }
	inline const Vector2& velocity() const { return m_velocity; }
	inline float angularVelocity() const { return m_angularVelocity; }
	inline float mass() const { return m_mass; }
	inline float rotation() const { return m_rotation; }
	inline bool immovable() const { return m_immovable; }
	inline OrientedBoundingBox& shape() { return m_shape; }

	inline void position(const Vector2& position) { m_position = position; }
	inline void velocity(const Vector2& velocity) { m_velocity = velocity; }
	inline void angularVelocity(float angularVelocity) { m_angularVelocity = angularVelocity; }
	inline void mass(float mass) { m_mass = mass; }
	inline void rotation(float rotation) { m_rotation = rotation; }
	inline void shape(const OrientedBoundingBox& shape) { m_shape = shape; }
	inline void immovable(bool immovable) { m_immovable = immovable; }

private:
	friend class PhysicsSimulation;
	PhysicsObject(float mass, const Vector2& position, const OrientedBoundingBox& shape);
	PhysicsObject();

	Vector2 m_position, m_velocity;
	float m_angularVelocity;
	float m_mass;
	float m_rotation;
	bool m_immovable;
	OrientedBoundingBox m_shape;
};

#endif // PhysicObject_h__
