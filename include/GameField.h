#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Globals.h"

class FieldCell;

class GameField
{
protected:
	GameField();

	static GameField* game_field_;
public:
	static GameField* get_instance();

	void setup_game_field(FIELD_SIZE field_size);

	void set_field_visuals(FIELD_SIZE field_size);

	void send_render_information();

	sf::Sprite* get_field_sprite();

private:
	FIELD_SIZE field_size = FIELD_SIZE::SIZE_3x3;

	sf::Texture* field_texture;
	sf::Sprite* field_sprite;

	std::vector<FieldCell*> field_cells_array;
};