#include <SFML/Graphics.hpp>
#include "Human.h"
#include "Renderer.h"
#include "GameField.h"

Human::Human(){}


bool Human::do_action(CELL_TYPE player_cell_type)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mouse_position(sf::Mouse::getPosition(*Renderer::get_renderer()->get_window()));
		return GameField::get_instance()->try_to_fill_cell(mouse_position, player_cell_type);
	}
	return false;
}
