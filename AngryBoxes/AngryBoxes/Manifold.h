#ifndef Manifold_h__
#define Manifold_h__

#include "Vector2.h"

class PhysicsObject;
class PhysicsSimulation;

class Manifold
{
public:
	PhysicsSimulation *simulation;
	PhysicsObject *a;
	PhysicsObject *b;

	int contactCount;
	float penetrationAmount;
	Vector2 normal;
	Vector2 contactPoints[2];

	float restitution;
	float dynamicFriction;
	float staticFriction;

	Manifold(PhysicsSimulation *simulation, PhysicsObject *a, PhysicsObject *b) : a(a), b(b), simulation(simulation) { }

	void solve();
	void init(float dt);
	void applyImpulse();
	void solvePosition();
	void solveInfiniteMass();
private:

};

#endif // Manifold_h__
