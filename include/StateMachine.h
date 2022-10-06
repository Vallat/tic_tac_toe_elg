#pragma once

class SetupMenu;
class Player;
class ResultDisplay;

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

	void switch_state(STATES new_state);

	void initialize_game();

private:
	STATES current_state = STATES::STATE_SETUP;

	SetupMenu* setup_menu;

	Player* player_one;
	Player* player_two;
};