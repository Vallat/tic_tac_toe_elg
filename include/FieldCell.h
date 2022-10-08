#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.h"

const std::string CROSS_IMAGE_PATH = "resources/cross.png";
const std::string ZERO_IMAGE_PATH = "resources/zero.png";


/// <summary>
/// Cell can have three types that used both for displaying and gameplay purposes
/// </summary>
enum class CELL_TYPE
{
	CELL_EMPTY,
	CELL_CROSS,
	CELL_ZERO,
};

class FieldCell
{
public:
	FieldCell();
	FieldCell(sf::Vector2f cell_pos_, sf::Vector2f screen_offset_);
	void set_current_type(CELL_TYPE new_type);
	CELL_TYPE get_current_type();
	
	sf::Sprite* get_sprite();

	sf::Vector2f get_cell_pos();

	void update_visuals();

	bool is_hovered(sf::Vector2f mouse_position);

	bool is_empty();

	sf::Vector2f get_cell_center_pos();

private:
	/// <summary>
	/// Cell position on the screen without offset
	/// </summary>
	sf::Vector2f cell_pos;

	/// <summary>
	/// Offset to the cell_pos that is relative to the distance from the screen edge to the game field
	/// </summary>
	sf::Vector2f screen_offset;

	sf::Texture* texture = nullptr;
	sf::Sprite* sprite = nullptr;

	CELL_TYPE current_type = CELL_TYPE::CELL_EMPTY;

};