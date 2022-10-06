#include "Button.h"

Button::Button(const std::string& texture_path, sf::Vector2f scale)
{
	texture = new sf::Texture;
	if (!texture->loadFromFile(texture_path))
	{
		throw std::runtime_error("Button: Didn't manage to load button with texture " + texture_path);
	}
	texture->setSmooth(false);

	sf::Sprite* current_sprite = new sf::Sprite;
	current_sprite->setTexture(*texture);
	current_sprite->setScale(scale);

	sf::FloatRect text_rect = current_sprite->getLocalBounds();
	current_sprite->setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height);

	set_sprite(current_sprite);
}


void Button::set_sprite(sf::Sprite* sprite_)
{
	sprite = sprite_;
}

sf::Sprite* Button::get_sprite()
{
	return sprite;
}


bool Button::is_hovered(sf::Vector2f mouse_position)
{
	sf::FloatRect float_rect = sprite->getGlobalBounds();
	return float_rect.contains(mouse_position);
}

bool Button::is_clicked(sf::Vector2f mouse_position)
{
	if (!is_hovered(mouse_position))
	{
		return false;
	}
	return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}


void Button::set_position(sf::Vector2f new_position)
{
	sf::Sprite* current_sprite = get_sprite();
	current_sprite->setPosition(new_position);
}

sf::Vector2f Button::get_position()
{
	sf::Sprite* current_sprite = get_sprite();
	return current_sprite->getPosition();
}