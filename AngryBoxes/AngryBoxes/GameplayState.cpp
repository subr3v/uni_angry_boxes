#include "GameplayState.h"

void GamePlayState::runSimulation()
{
	if(isSimulationStage == true)
	{
		simulation.step(1.0f / 60.0f);
		//isInputStage = true;
	}

	if(GameInput->getReleaseBox() == true)
	{
		GameInput->setReleaseBox(false);
	}
}

void GamePlayState::runInput()
{
	if(isInputStage == true)
	{
		//GameInput->getInput();
	}

	if(GameInput->getReleaseBox() == true)
	{
		isSimulationStage = true;
		releaseBox();
		isInputStage = false;
	}
}

//Sets states to default upon moving to GamePlayState
void GamePlayState::Start()
{
	isInputStage = true;
	isSimulationStage = false;
	isCurrentState = true;
	simulation.gravity(Vector2(0, 3.8f));

	PhysicsObject* ground = simulation.createObject(0, Vector2(400, 600 - 60), OrientedBoundingBox(Vector2(0, 0), 800, 120, 0));
	
	for( int x = 0; x < 8; x++ )
	{
		for( int y = 0; y < 6; y++)
		{
			levelObjects.push_back(simulation.createObject(0, Vector2(150, 600 - 380) + Vector2(x * 25, y * 25), OrientedBoundingBox(Vector2(0, 0), 25, 25, 0)));
		}
	}
}

void GamePlayState::End()
{
	isInputStage = false;
	isSimulationStage = false;
	isCurrentState = false;
}

//Launches box if appropriate
void GamePlayState::releaseBox()
{
	if(isInputStage == true)
	{
	
		float xLength = 0;
		float yLength = 0;
		float releaseAngle = 0;
		float releaseVelocity = 0;
		float xVelocity = 0;
		float yVelocity = 0;

		xLength = GameInput->getXDragStart() - GameInput->getXDragEnd();
		yLength = GameInput->getYDragStart() - GameInput->getXDragEnd();

		//Setting x Length to 1 to avoid division by 0
		if(xLength == 0)
		{
			xLength = 1;
		}

		releaseAngle = -atan(yLength/xLength);

		releaseVelocity =  sqrt(pow(xLength, 2) + pow(yLength, 2)) * VELOCITY_MOD;

		yVelocity = sin(releaseAngle) * 250;
		xVelocity = cos(releaseAngle) * 250;

		vector.x = xVelocity;
		vector.y = yVelocity;

		std::cout << "Stuff happening" << vector.x << vector.y << std::endl;

		PhysicsObject* obj = simulation.createObject(50, Vector2(25, 380), OrientedBoundingBox(Vector2(0, 0), 5, 5, 0));
		obj->restitution = 1;
		obj->velocity = Vector2(xVelocity, yVelocity);


		for(int i = 0; i < levelObjects.size(); i++)
		{
			levelObjects[i]->mass = 5;
			levelObjects[i]->inverseMass = 1 / 5.0f;
		}
	}

	//Pass bird to sim and start sim
	GameInput->setReleaseBox(false);
}