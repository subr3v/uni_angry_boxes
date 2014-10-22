#ifndef GameState_h__
#define GameState_h__


class GameState
{
public: 
	GameState();
	bool getCurrentState();
	void setCurrentState(bool);

protected:

	bool isCurrentState;

};

#endif // GameState_h__
