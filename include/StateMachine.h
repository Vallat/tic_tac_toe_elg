#pragma once

class SetupMenu;
class Player;

enum class STATES
{
	STATE_SETUP,
	STATE_PLAYER1_TURN,
	STATE_PLAYER2_TURN,
	STATE_RESULT_DISPLAY,
};

class StateMachine
{
public:
	StateMachine();
	
	void process();

private:
	STATES current_state = STATES::STATE_SETUP;

	SetupMenu* setup_menu;

	Player* player_one;
	Player* player_two;
};