#include "GameField.h"
#include "Renderer.h"
#include "FieldCell.h"
#include <iostream>


GameField* GameField::game_field_ = nullptr;

GameField* GameField::get_instance()
{
	if (game_field_ == nullptr)
	{
		game_field_ = new GameField();
	}
	return game_field_;
}


GameField::GameField()
{
	field_texture = nullptr;
	field_sprite = nullptr;
	last_filled_cell = nullptr;
}


void GameField::setup_game_field(FIELD_SIZE field_size_)
{
	field_size = field_size_;
	set_field_visuals(field_size);

	size_t line_size = (field_size == FIELD_SIZE::SIZE_3x3) ? 3 : 5;
	size_t array_len = line_size * line_size;

	if (field_cells_array.size() == array_len)
	{
		return;
	}
	else
	{
		field_cells_array.clear();
	}

	sf::Vector2f screen_offset = sf::Vector2f((WINDOW_WIDTH - get_field_sprite()->getGlobalBounds().width) / 2.0f, (WINDOW_HEIGHT - get_field_sprite()->getGlobalBounds().height) / 2.0f);
	for (size_t y = 0; y < line_size; y++)
	{
		for (size_t x = 0; x < line_size; x++)
		{
			FieldCell* field_cell = new FieldCell(sf::Vector2f(x, y), screen_offset);
			field_cells_array.push_back(field_cell);
		}
	}
}


void GameField::set_field_visuals(FIELD_SIZE field_size)
{
	const std::string file_path = (field_size == FIELD_SIZE::SIZE_3x3) ? "resources/field_size_3.png" : "resources/field_size_5.png";
	sf::Texture* field_texture_ = new sf::Texture;
	if (!field_texture_->loadFromFile(file_path))
	{
		throw std::runtime_error("Renderer: Didn't manage to load game field texture " + file_path);
	}

	field_texture = field_texture_;
	sf::Sprite* field_sprite_ = new sf::Sprite;
	field_sprite_->setTexture(*field_texture_);
	field_sprite_->setOrigin(field_sprite_->getLocalBounds().width / 2.0f, field_sprite_->getLocalBounds().height / 2.0f);
	field_sprite_->setPosition(Renderer::get_renderer()->get_window()->getView().getCenter());
	field_sprite = field_sprite_;
}


void GameField::send_render_information()
{
	sf::Sprite* field_sprite_ = get_field_sprite();
	if (field_sprite_ == nullptr)
	{
		return;
	}

	Renderer::get_renderer()->window_draw(*field_sprite_);

	for (size_t iterator = 0; iterator < field_cells_array.size(); iterator++)
	{
		FieldCell* field_cell = field_cells_array[iterator];
		sf::Sprite* field_cell_sprite = field_cell->get_sprite();
		if (field_cell_sprite == nullptr)
		{
			continue;
		}
		Renderer::get_renderer()->window_draw(*field_cell_sprite);
	}

}


sf::Sprite* GameField::get_field_sprite()
{
	return field_sprite;
}


bool GameField::try_to_fill_cell(sf::Vector2f mouse_position, CELL_TYPE cell_type)
{
	for (size_t iterator = 0; iterator < field_cells_array.size(); iterator++)
	{
		FieldCell* field_cell = field_cells_array[iterator];
		if (!field_cell->is_hovered(mouse_position))
		{
			continue;
		}
		if (field_cell->is_empty())
		{
			field_cell->set_current_type(cell_type);
			field_cell->update_visuals();
			last_filled_cell = field_cell;
			return true;
		}
	}
	return false;
}


bool GameField::check_for_win_condition(CELL_TYPE win_type)
{
	size_t line_len = (field_size == FIELD_SIZE::SIZE_3x3) ? 3 : 5;
	CELL_TYPE last_cell_type = win_type;

	size_t last_filled_x = last_filled_cell->get_cell_pos().x;
	size_t last_filled_y = last_filled_cell->get_cell_pos().y;

	bool win_condition_horiz = true, win_condition_vert = true;
	for (size_t i = 0; i < line_len; i++)
	{
		// check for vertical line
		win_condition_vert &= (field_cells_array[last_filled_x + (i * line_len)]->get_current_type() == win_type);
		// check for horizontal line
		win_condition_horiz &= (field_cells_array[i + (last_filled_y * line_len)]->get_current_type() == win_type);
	}


	// if there are no horizontal and vertical win conditions - check diagonals
	if (!(win_condition_horiz || win_condition_vert))
	{
		bool win_condition_diag_main = true, win_condition_diag_add = true;
		for (size_t i = 0; i < line_len; i++)
		{
			win_condition_diag_main &= (field_cells_array[i + i * line_len]->get_current_type() == win_type);
			win_condition_diag_add &= (field_cells_array[line_len - i - 1 + i * line_len]->get_current_type() == win_type);
		}
		return win_condition_diag_main || win_condition_diag_add;
	}

	return win_condition_vert || win_condition_horiz;
}


void GameField::clear_field()
{
	for (size_t iterator = 0; iterator < field_cells_array.size(); iterator++)
	{
		FieldCell* field_cell = field_cells_array[iterator];
		field_cell->set_current_type(CELL_TYPE::CELL_EMPTY);
		field_cell->update_visuals();
	}
	field_sprite = nullptr;
}
