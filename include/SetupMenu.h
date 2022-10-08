#pragma once

#include <SFML/Graphics.hpp>
#include <Globals.h>

class Button;

class SetupMenu
{
public:
	SetupMenu();

	/// <summary>
	/// Scans user mouse input to handle buttons pressing and change game settings
	/// </summary>
	/// <returns>true if "Start" button was pressed</returns>
	bool process();

	/// <summary>
	/// Renderes all buttons
	/// </summary>
	void render_buttons();

	FIELD_SIZE get_field_size();
	GAME_MODE get_game_mode();

private:
	FIELD_SIZE field_size = FIELD_SIZE::SIZE_3x3;
	GAME_MODE game_mode = GAME_MODE::MODE_PvsAI;

	Button* size_buttons[2];
	Button* mode_buttons[3];
	Button* start_button;
};