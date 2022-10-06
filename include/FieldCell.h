#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.h"

const std::string CROSS_IMAGE_PATH = "resources/cross.png";
const std::string ZERO_IMAGE_PATH = "resources/zero.png";

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

	void update_visuals();

private:
	sf::Vector2f cell_pos;
	sf::Vector2f screen_offset;

	sf::Texture* texture = nullptr;
	sf::Sprite* sprite = nullptr;

	CELL_TYPE current_type = CELL_TYPE::CELL_EMPTY;

};