#include "StateMachine.h"
#include "Player.h"
#include "Human.h"
#include "AI.h"
#include "SetupMenu.h"
#include "GameField.h"
#include "ResultDisplay.h"
#include "FieldCell.h"
#include <thread>
#include <iostream>

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
			std::this_thread::sleep_for(std::chrono::milliseconds(300));
		}
		break;
	case STATES::STATE_PLAYER1_TURN:
		if (player_one->do_action(CELL_TYPE::CELL_CROSS))
		{
			if (GameField::get_instance()->check_for_draft())
			{
				ResultDisplay::get_instance()->set_up_win_result(WIN_RESULT::DRAFT);
				switch_state(STATES::STATE_RESULT_DISPLAY);
			}
			else if (GameField::get_instance()->check_for_win_condition(CELL_TYPE::CELL_CROSS))
			{
				ResultDisplay::get_instance()->set_up_win_result(WIN_RESULT::CROSS_WIN);
				switch_state(STATES::STATE_RESULT_DISPLAY);
			}
			else
			{
				switch_state(STATES::STATE_PLAYER2_TURN);
			}
		}
		break;
	case STATES::STATE_PLAYER2_TURN:
		if (player_two->do_action(CELL_TYPE::CELL_ZERO))
		{
			if (GameField::get_instance()->check_for_draft())
			{
				ResultDisplay::get_instance()->set_up_win_result(WIN_RESULT::DRAFT);
				switch_state(STATES::STATE_RESULT_DISPLAY);
			}
			else if (GameField::get_instance()->check_for_win_condition(CELL_TYPE::CELL_ZERO))
			{
				ResultDisplay::get_instance()->set_up_win_result(WIN_RESULT::ZERO_WIN);
				switch_state(STATES::STATE_RESULT_DISPLAY);
			}
			else
			{
				switch_state(STATES::STATE_PLAYER1_TURN);
			}
		}
		break;
	case STATES::STATE_RESULT_DISPLAY:
		if (!ResultDisplay::get_instance()->process())
		{
			GameField::get_instance()->clear_field();
			switch_state(STATES::STATE_SETUP);
		}
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
	size_t line_len = (game_field->get_field_size() == FIELD_SIZE::SIZE_3x3) ? 3 : 5;

	switch (setup_menu->get_game_mode())
	{
	case GAME_MODE::MODE_PvsP:
		player_one = new Human;
		player_two = new Human;
		break;
	case GAME_MODE::MODE_PvsAI:
		player_one = new Human;
		player_two = new AI(game_field->get_field_size());
		break;
	case GAME_MODE::MODE_AIvsAI:
		player_one = new AI(game_field->get_field_size());
		player_two = new AI(game_field->get_field_size());
		break;
	}
}
