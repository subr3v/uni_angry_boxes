#include "GameState.h"
#include "InputManager.h"
#include "cmath"

#ifndef GameplayState_h__
#define GameplayState_h__

class GamePlayState : GameState
{

#define VELOCITY_MOD 0.5f; //Modifier to change velocity to workable number

public:
	void Start(); //Sets states to default upon moving to GamePlayState
	void End(); //Sets states to false when moving to another state
	void runSimulation();
	void runInput();

protected:
	InputManager* GameInput;
	bool isInputStage;
	bool isSimulationStage;
	void releaseBox();

};

#endif // GameplayState_h__
