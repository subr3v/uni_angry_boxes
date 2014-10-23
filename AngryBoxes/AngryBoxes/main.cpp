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
	
	simulation.gravity(Vector2(0, 3.8f));

	/*
	PhysicsObject* obj = simulation.createObject(1, Vector2(50, 300), OrientedBoundingBox(Vector2(0, 0), 10, 50, 0));
	//PhysicsObject* obj1 = simulation.createObject(0, Vector2(100, 200), OrientedBoundingBox(Vector2(0, 0), 400, 120, 20));
	PhysicsObject* obj2 = simulation.createObject(1, Vector2(260, 20), OrientedBoundingBox(Vector2(0, 0), 10, 50, 20));
	PhysicsObject* obj4 = simulation.createObject(1, Vector2(260, 320), OrientedBoundingBox(Vector2(0, 0), 10, 50, 20));
	PhysicsObject* obj3 = simulation.createObject(1, Vector2(200, 20), OrientedBoundingBox(Vector2(0, 0), 10, 50, 20));
	PhysicsObject* g2 = simulation.createObject(0, Vector2(600, 600 - 400), OrientedBoundingBox(Vector2(0, 0), 50, 400, 0));
	*/

	PhysicsObject* ground = simulation.createObject(0, Vector2(400, 600 - 60), OrientedBoundingBox(Vector2(0, 0), 800, 120, 0));

	const float kDt = 1.0f / 60.0f;

	std::vector<PhysicsObject*> levelObjects;

	for( int x = 0; x < 8; x++ )
	{
		for( int y = 0; y < 6; y++)
		{
			levelObjects.push_back(simulation.createObject(0, Vector2(150, 600 - 380) + Vector2(x * 25, y * 25), OrientedBoundingBox(Vector2(0, 0), 25, 25, 0)));
		}
	}

	bool thrown = false;

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

		if ( thrown == false && input.IsButtonPressed())
		{
			for(int i = 0; i< levelObjects.size(); i++)
			{
				levelObjects[i]->mass = 5;
				levelObjects[i]->inverseMass = 1 / 5.0f;
			}
			PhysicsObject* obj = simulation.createObject(5000, Vector2(25, 380), OrientedBoundingBox(Vector2(0, 0), 5, 5, 0));
			obj->restitution = 1;
			obj->velocity = Vector2(100, -50);
			thrown = true;
		}

		simulation.step(kDt * 2.0f);

		graphicsContext.SwapBuffers();
	}

    return 0;
}