#include "StateMachine.h"
#include "Player.h"
#include "Human.h"
#include "AI.h"
#include "SetupMenu.h"
#include "GameField.h"

StateMachine::StateMachine()
{
	setup_menu = new SetupMenu();
	player_one = nullptr;
	player_two = nullptr;
}


void StateMachine::process()
{
	switch (current_state)
	{
	case STATES::STATE_SETUP:
		if (setup_menu->process())
		{
			initialize_game();
			switch_state(STATES::STATE_PLAYER1_TURN);
		}
		break;
	case STATES::STATE_PLAYER1_TURN:
		if (player_one->do_action())
		{
			switch_state(STATES::STATE_PLAYER2_TURN);
		}
		break;
	case STATES::STATE_PLAYER2_TURN:
		if (player_two->do_action())
		{
			switch_state(STATES::STATE_PLAYER1_TURN);
		}
		break;
	case STATES::STATE_RESULT_DISPLAY:
		break;
	default:
		break;
	}
}


void StateMachine::switch_state(STATES new_state)
{
	current_state = new_state;
}


void StateMachine::initialize_game()
{
	GameField* game_field = GameField::get_instance();

	game_field->setup_game_field(setup_menu->get_field_size());

	switch (setup_menu->get_game_mode())
	{
	case GAME_MODE::MODE_PvsP:
		player_one = new Human;
		player_two = new Human;
		break;
	case GAME_MODE::MODE_PvsAI:
		player_one = new Human;
		player_two = new AI;
		break;
	case GAME_MODE::MODE_AIvsAI:
		player_one = new AI;
		player_two = new AI;
		break;
	}
}
