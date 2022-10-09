#pragma once

#include "SFML/Graphics.hpp"

class FieldCell;

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

	/// <summary>
	/// Handles timer to be able to vanish text after a set perioud of time and switch StateMachine on next state
	/// </summary>
	bool process();

	/// <summary>
	/// Gives renderer text and win_line sprites to draw them
	/// </summary>
	void send_render_information();

	/// <summary>
	/// Generates text that depends on the given win result
	/// </summary>
	void set_up_win_result(WIN_RESULT win_result);

	/// <summary>
	/// Draws a line that goes through the win line on the game field 
	/// </summary>
	void draw_win_line(std::vector<FieldCell*> win_line);

	void clear_win_line();

private:
	sf::Clock* timer = nullptr;

	sf::Font loaded_font;

	sf::Text* displayed_text;

//	sf::RectangleShape* win_line = nullptr;

	sf::Vertex win_line[4];
};