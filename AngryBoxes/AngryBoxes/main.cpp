#include "GraphicsContext.h"

#include "OrientedBoundingBox.h"
#include "PhysicsSimulation.h"
#include "PhysicObject.h"
#include "InputManager.h"

#define M_PI 3.14159265358979323846

int main()
{

	InputManager input;
    // create the window
    //sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	GraphicsContext graphicsContext;
	input.init(graphicsContext.getWindow());
	PhysicsSimulation simulation;
	
	simulation.gravity(Vector2(0, 2.8f));

	PhysicsObject* obj = simulation.createObject(1, Vector2(50, 300), OrientedBoundingBox(Vector2(0, 0), 10, 50, 0));
	//PhysicsObject* obj1 = simulation.createObject(0, Vector2(100, 200), OrientedBoundingBox(Vector2(0, 0), 400, 120, 20));
	PhysicsObject* obj2 = simulation.createObject(1, Vector2(260, 20), OrientedBoundingBox(Vector2(0, 0), 10, 50, 20));
	PhysicsObject* obj4 = simulation.createObject(1, Vector2(260, 320), OrientedBoundingBox(Vector2(0, 0), 10, 50, 20));
	PhysicsObject* obj3 = simulation.createObject(1, Vector2(200, 20), OrientedBoundingBox(Vector2(0, 0), 10, 50, 20));
	PhysicsObject* ground = simulation.createObject(0, Vector2(300, 600 - 120), OrientedBoundingBox(Vector2(0, 0), 600, 120, 0));
	PhysicsObject* g2 = simulation.createObject(0, Vector2(600, 600 - 400), OrientedBoundingBox(Vector2(0, 0), 50, 400, 0));

	//ground->rotation = /30;

	obj->force = Vector2(150, -100);
	obj->rotation = -45;
	obj2->rotation = 45;

	while (true)
	{
		input.getInput();
		graphicsContext.Update();
		graphicsContext.Clear();

		const std::vector<PhysicsObject*>& objs = simulation.getObjects();
		for(int i = 0; i < objs.size(); i++)
		{
			graphicsContext.DrawOrientedBoundingBox(objs[i]->shape);
		}

		if (input.IsButtonPressed())
		{
			obj->applyImpulse(Vector2(1, 0), obj->position);
		}

		simulation.step(1.0f / 60.0f);

		graphicsContext.SwapBuffers();
	}

    return 0;
}