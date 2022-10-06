#include "GameField.h"
#include "Renderer.h"
#include "FieldCell.h"


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
}


void GameField::setup_game_field(FIELD_SIZE field_size_)
{
	field_size = field_size_;
	set_field_visuals(field_size);

	size_t line_size = (field_size == FIELD_SIZE::SIZE_3x3) ? 3 : 5;
	size_t array_len = line_size * line_size;

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

	size_t array_len = (field_size == FIELD_SIZE::SIZE_3x3) ? 9 : 25;
	for (size_t iterator = 0; iterator < array_len; iterator++)
	{
		FieldCell* field_cell = field_cells_array[iterator];
		Renderer::get_renderer()->window_draw(*field_cell->get_sprite());
	}

}


sf::Sprite* GameField::get_field_sprite()
{
	return field_sprite;
}
