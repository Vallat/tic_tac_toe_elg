#pragma once
#include <SFML/Graphics.hpp>

class Renderer
{
public:
	Renderer(unsigned int window_width_, unsigned int window_height_);
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

private:
	sf::RenderWindow* display_window = nullptr;
};
