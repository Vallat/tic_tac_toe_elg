#include "Renderer.h"
#include "Globals.h"

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
	field_sprite = nullptr;
	field_texture = nullptr;
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


void Renderer::window_display()
{
	if (field_sprite != nullptr)
	{
		window_draw(*field_sprite);
	}
	sf::RenderWindow* game_window = get_window();
	game_window->display();
}


void Renderer::set_field_visuals(FIELD_SIZE field_size)
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
	field_sprite_->setPosition(get_window()->getView().getCenter());
	field_sprite = field_sprite_;
}
