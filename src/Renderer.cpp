#include "Renderer.h"
#include "Globals.h"
#include "GameField.h"
#include "ResultDisplay.h"

Renderer* Renderer::renderer_ = nullptr;

Renderer* Renderer::get_renderer()
{
	if (renderer_ == nullptr)
	{
		renderer_ = new Renderer;
	}
	return renderer_;
}


Renderer::Renderer()
{
	display_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);
	if (display_window == nullptr)
	{
		throw std::runtime_error("Renderer: Display window was not initialized!");
	}
}


sf::RenderWindow* Renderer::get_window()
{
	return display_window;
}


void Renderer::window_clear()
{
	sf::RenderWindow* game_window = get_window();
	game_window->clear();
}


void Renderer::window_draw(sf::Sprite sprite_to_draw)
{
	sf::RenderWindow* game_window = get_window();
	game_window->draw(sprite_to_draw);
}

void Renderer::window_draw(sf::Text text_to_draw)
{
	sf::RenderWindow* game_window = get_window();
	game_window->draw(text_to_draw);
}

void Renderer::window_draw(sf::Vertex vertex_to_draw[])
{
	sf::RenderWindow* game_window = get_window();
	game_window->draw(vertex_to_draw, 100, sf::Quads);
}


void Renderer::window_display()
{
	GameField* game_field = GameField::get_instance();
	game_field->send_render_information();

	ResultDisplay* result_display = ResultDisplay::get_instance();
	result_display->send_render_information();

	sf::RenderWindow* game_window = get_window();
	game_window->display();
}

