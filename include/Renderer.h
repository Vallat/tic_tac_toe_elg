#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"

class Renderer
{
protected:
	Renderer();
	
	static Renderer* renderer_;
	sf::RenderWindow* display_window = nullptr;

public:
	static Renderer* get_renderer();

	sf::RenderWindow* get_window();

	/// <summary>
	/// clears the display window
	/// </summary>
	void window_clear();

	/// <summary>
	/// Is used for drawing sprite or text on the display window
	/// </summary>
	void window_draw(sf::Sprite sprite_to_draw);
	void window_draw(sf::Text text_to_draw);

	/// <summary>
	/// Is used for displaying everything that was passed to the display window with window_draw()
	/// </summary>
	void window_display();

	void set_field_visuals(FIELD_SIZE field_size);

private:
	sf::Texture* field_texture;
	sf::Sprite* field_sprite;
};
