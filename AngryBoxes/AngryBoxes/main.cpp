#include "GraphicsContext.h"

#include "OrientedBoundingBox.h"
#include "PhysicsSimulation.h"
#include "PhysicObject.h"

#define M_PI 3.14159265358979323846

int main()
{
    // create the window
    //sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	GraphicsContext graphicsContext;
	
	PhysicsSimulation simulation;
	
	simulation.gravity(Vector2(0, 9.8f));

	PhysicsObject* obj = simulation.createObject(50, Vector2(150, 150), OrientedBoundingBox(Vector2(0, 0), 50, 50, 0));
	PhysicsObject* obj1 = simulation.createObject(50, Vector2(180, 150), OrientedBoundingBox(Vector2(0, 0), 50, 50, 0));
	PhysicsObject* ground = simulation.createObject(100, Vector2(400, 600 - 120), OrientedBoundingBox(Vector2(0, 0), 600, 120, 0));
	ground->immovable(true);
	obj1->immovable(true);
	obj1->rotation(30.0f / 180.0f * M_PI);

	obj->angularVelocity(90.0f / 180.0f * M_PI);

	while (true)
	{
		graphicsContext.Update();
		graphicsContext.Clear();

		simulation.step(1.0f / 60.0f / 20.0f);
		
		const std::vector<PhysicsObject*>& objs = simulation.getObjects();
		for(int i = 0; i < objs.size(); i++)
		{
			graphicsContext.DrawOrientedBoundingBox(objs[i]->shape());
		}

		graphicsContext.SwapBuffers();
	}

    return 0;
}