#pragma once

#include "SFML/Graphics.hpp"

enum class WIN_RESULT
{
	CROSS_WIN,
	ZERO_WIN,
	DRAFT,
};

class ResultDisplay
{
protected:
	ResultDisplay();

	static ResultDisplay* result_display_;
public:
	static ResultDisplay* get_instance();

	bool process();

	void send_render_information();

	void set_up_win_result(WIN_RESULT win_result);

private:
	sf::Clock* timer = nullptr;

	sf::Font loaded_font;

	sf::Text* displayed_text;
};