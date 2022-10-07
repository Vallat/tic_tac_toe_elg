#include "FieldCell.h"

FieldCell::FieldCell() {}

FieldCell::FieldCell(sf::Vector2f cell_pos_, sf::Vector2f screen_offset_)
{
	cell_pos = cell_pos_;
	screen_offset = screen_offset_;
}


void FieldCell::set_current_type(CELL_TYPE new_type)
{
	current_type = new_type;
}

CELL_TYPE FieldCell::get_current_type()
{
	return current_type;
}


sf::Sprite* FieldCell::get_sprite()
{
	return sprite;
}


sf::Vector2f FieldCell::get_cell_pos()
{
	return cell_pos;
}


void FieldCell::update_visuals()
{
	if (current_type == CELL_TYPE::CELL_EMPTY)
	{
		sprite = nullptr;
		return;
	}
	const std::string texture_path = (current_type == CELL_TYPE::CELL_CROSS) ? CROSS_IMAGE_PATH : ZERO_IMAGE_PATH;
	sf::Texture* new_texture = new sf::Texture();
	if (!new_texture->loadFromFile(texture_path))
	{
		throw std::runtime_error("FieldCell: Didn't manage to load field cell with texture " + texture_path);
	}
	texture = new_texture;

	sf::Sprite* new_sprite = new sf::Sprite();
	new_sprite->setTexture(*texture);
	new_sprite->setPosition(
		sf::Vector2f(
			cell_pos.x * CELL_SIZE_PIXELS + ((cell_pos.x > 0) ? cell_pos.x * PARTING_LINE_SIZE_PIXELS : 0),
			cell_pos.y * CELL_SIZE_PIXELS + ((cell_pos.y > 0) ? cell_pos.y * PARTING_LINE_SIZE_PIXELS : 0)
		) + screen_offset
	);
	sprite = new_sprite;
}


bool FieldCell::is_hovered(sf::Vector2f mouse_position)
{
	sf::Sprite* current_sprite = get_sprite();
	sf::FloatRect float_rect;
	if (current_sprite == nullptr)
	{
		float_rect = sf::FloatRect(
			(
			sf::Vector2f(
				cell_pos.x * CELL_SIZE_PIXELS + ((cell_pos.x > 0) ? cell_pos.x * PARTING_LINE_SIZE_PIXELS : 0),
				cell_pos.y * CELL_SIZE_PIXELS + ((cell_pos.y > 0) ? cell_pos.y * PARTING_LINE_SIZE_PIXELS : 0)
			) + screen_offset
			),
			sf::Vector2f(
				CELL_SIZE_PIXELS,
				CELL_SIZE_PIXELS
			)
		);
	}
	else
	{
		float_rect = current_sprite->getGlobalBounds();

	}
	return float_rect.contains(mouse_position);
}


bool FieldCell::is_empty()
{
	return get_current_type() == CELL_TYPE::CELL_EMPTY;
}
