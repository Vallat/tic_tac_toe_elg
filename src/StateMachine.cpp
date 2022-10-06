#include "StateMachine.h"
#include "Player.h"
#include "SetupMenu.h"


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
			current_state = STATES::STATE_PLAYER1_TURN;
		}
		break;
	case STATES::STATE_PLAYER1_TURN:
		break;
	case STATES::STATE_PLAYER2_TURN:
		break;
	case STATES::STATE_RESULT_DISPLAY:
		break;
	default:
		break;
	}
}
