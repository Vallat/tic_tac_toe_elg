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

	/// <summary>
	/// Sets up field visuals, creates FieldCell objects depending on the given field size
	/// </summary>
	void setup_game_field(FIELD_SIZE field_size);

	/// <summary>
	/// Sets up field background sprite
	/// </summary>
	void set_field_visuals(FIELD_SIZE field_size);

	/// <summary>
	/// Gives renderer FieldCells sprites when it asks for them
	/// </summary>
	void send_render_information();

	sf::Sprite* get_field_sprite();

	FIELD_SIZE get_field_size();

	/// <summary>
	/// Tries to change given (or on given coordinates) cell's type on the given type, updates its visuals and assigns "last_filled_cell"
	/// </summary>
	/// <returns>true, if the change was successfull</returns>
	bool try_to_fill_cell(sf::Vector2f mouse_position, CELL_TYPE cell_type);
	bool try_to_fill_cell(FieldCell* cell_to_fill, CELL_TYPE cell_type);
	
	/// <summary>
	/// Checks each line and tells ResultDisplay singleton to draw a win line if the game field matches win conditions
	/// </summary>
	/// <returns>true if game field matches win conditions, false otherwise</returns>
	bool check_for_win_condition(CELL_TYPE win_type);

	/// <summary>
	/// Checks for draft - when there are no more empty cells
	/// </summary>
	/// <returns>true if all cells are not empty</returns>
	bool check_for_draft();

	/// <summary>
	/// Clears the game field, resetting FieldCells types and visuals, setting field sprite to null
	/// </summary>
	void clear_field();

	std::vector<FieldCell*> get_field_cells_array();

	FieldCell* get_last_filled_cell();

private:
	FIELD_SIZE field_size = FIELD_SIZE::SIZE_3x3;

	sf::Texture* field_texture;
	sf::Sprite* field_sprite;

	std::vector<FieldCell*> field_cells_array;

	FieldCell* last_filled_cell;
};