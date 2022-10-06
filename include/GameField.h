#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Globals.h"

class FieldCell;
enum class CELL_TYPE;

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

	bool try_to_fill_cell(sf::Vector2f mouse_position, CELL_TYPE cell_type);

	bool check_for_win_condition(CELL_TYPE win_type);

	void clear_field();

private:
	FIELD_SIZE field_size = FIELD_SIZE::SIZE_3x3;

	sf::Texture* field_texture;
	sf::Sprite* field_sprite;

	std::vector<FieldCell*> field_cells_array;

	FieldCell* last_filled_cell;
};