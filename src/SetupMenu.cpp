#include "SetupMenu.h"
#include "Button.h"
#include "Globals.h"
#include "Renderer.h"

SetupMenu::SetupMenu()
{
	Renderer* renderer = Renderer::get_renderer();
	sf::Vector2f screen_center = renderer->get_window()->getView().getCenter();

	Button* field_size3_button = new Button("resources/button_3x3.png", ICONS_SCALE);
	field_size3_button->set_position(screen_center + FIELD_SIZE3_BUTTON_OFFSET);
	size_buttons[0] = field_size3_button;

	Button* field_size5_button = new Button("resources/button_5x5.png", ICONS_SCALE);
	field_size5_button->set_position(screen_center + FIELD_SIZE5_BUTTON_OFFSET);
	field_size5_button->get_sprite()->setColor(sf::Color(120, 120, 120));
	size_buttons[1] = field_size5_button;

	Button* mode_pvp_button = new Button("resources/button_PvsP.png", ICONS_SCALE);
	mode_pvp_button->set_position(screen_center + MODE_PvP_BUTTON_OFFSET);
	mode_pvp_button->get_sprite()->setColor(sf::Color(120, 120, 120));
	mode_buttons[0] = mode_pvp_button;

	Button* mode_pvai_button = new Button("resources/button_PvsAI.png", ICONS_SCALE);
	mode_pvai_button->set_position(screen_center + MODE_PvAI_BUTTON_OFFSET);
	mode_buttons[1] = mode_pvai_button;

	Button* mode_aivai_button = new Button("resources/button_AivsAI.png", ICONS_SCALE);
	mode_aivai_button->set_position(screen_center + MODE_AIvAI_BUTTON_OFFSET);
	mode_aivai_button->get_sprite()->setColor(sf::Color(120, 120, 120));
	mode_buttons[2] = mode_aivai_button;

	Button* start_game_button = new Button("resources/button_start.png", ICONS_SCALE);
	start_game_button->set_position(screen_center + GAME_START_BUTTON_OFFSET);
	start_button = start_game_button;
}


bool SetupMenu::process()
{
	render_buttons();

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		return false;
	}
	sf::Vector2f mouse_position(sf::Mouse::getPosition(*Renderer::get_renderer()->get_window()));
	if (size_buttons[0]->is_hovered(mouse_position))
	{
		size_buttons[0]->get_sprite()->setColor(sf::Color(255, 255, 255));
		size_buttons[1]->get_sprite()->setColor(sf::Color(120, 120, 120));
		field_size = FIELD_SIZE::SIZE_3x3;
		return false;
	}
	else if (size_buttons[1]->is_hovered(mouse_position))
	{
		size_buttons[0]->get_sprite()->setColor(sf::Color(120, 120, 120));
		size_buttons[1]->get_sprite()->setColor(sf::Color(255, 255, 255));
		field_size = FIELD_SIZE::SIZE_5x5;
		return false;
	}

	size_t button_clicked = 0;
	for (size_t iterator = 0; iterator < 3; iterator++)
	{
		if (!mode_buttons[iterator]->is_hovered(mouse_position))
		{
			continue;
		}
		button_clicked = iterator + 1;
	}

	if (button_clicked)
	{
		for (size_t iterator = 1; iterator < 4; iterator++)
		{
			if (iterator == button_clicked)
			{
				mode_buttons[iterator - 1]->get_sprite()->setColor(sf::Color(255, 255, 255));
				continue;
			}
			mode_buttons[iterator - 1]->get_sprite()->setColor(sf::Color(120, 120, 120));
		}
		game_mode = static_cast<GAME_MODE>(button_clicked - 1);
		return false;
	}

	if (start_button->is_hovered(mouse_position))
	{
		Renderer::get_renderer()->window_clear();
		return true;
	}

	return false;
}


void SetupMenu::render_buttons()
{
	Renderer* renderer = Renderer::get_renderer();
	for (size_t iterator = 0; iterator < 2; iterator++)
	{
		renderer->window_draw(*size_buttons[iterator]->get_sprite());
	}

	for (size_t iterator = 0; iterator < 3; iterator++)
	{
		renderer->window_draw(*mode_buttons[iterator]->get_sprite());
	}

	renderer->window_draw(*start_button->get_sprite());
}


FIELD_SIZE SetupMenu::get_field_size()
{
	return field_size;
}


GAME_MODE SetupMenu::get_game_mode()
{
	return game_mode;
}
