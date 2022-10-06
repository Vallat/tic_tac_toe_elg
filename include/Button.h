#pragma once
#include <SFML/Graphics.hpp>

class Button
{
public:
	Button(const std::string& texture_path, sf::Vector2f scale);

	void set_sprite(sf::Sprite* sprite_);
	sf::Sprite* get_sprite();

	/// <summary>
	/// Is used for checking if button is currently hovered by the mouse passing the mouse position as an argument
	/// </summary>
	bool is_hovered(sf::Vector2f mouse_position);

	/// <summary>
	/// Is used for checking if button was clicked by the user passing the mouse position as an argument
	/// </summary>
	bool is_clicked(sf::Vector2f mouse_position);

	void set_position(sf::Vector2f new_position);
	sf::Vector2f get_position();

private:
	sf::Texture* texture;
	sf::Sprite* sprite;
};
