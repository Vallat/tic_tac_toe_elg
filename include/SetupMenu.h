#pragma once

#include <SFML/Graphics.hpp>
#include <Globals.h>

class Button;

class SetupMenu
{
public:
	SetupMenu();

	bool process();
	void render_buttons();

private:
	FIELD_SIZE field_size = FIELD_SIZE::SIZE_3x3;
	GAME_MODE game_mode = GAME_MODE::MODE_PvsAI;

	Button* size_buttons[2];
	Button* mode_buttons[3];
	Button* start_button;
};