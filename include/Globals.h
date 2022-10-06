#pragma once

enum class FIELD_SIZE
{
	SIZE_3x3,
	SIZE_5x5,
};

enum class GAME_MODE
{
	MODE_PvsP,
	MODE_PvsAI,
	MODE_AIvsAI,
};

const sf::String WINDOW_NAME = "Tic Tac Toe";
const unsigned int WINDOW_HEIGHT = 700;
const unsigned int WINDOW_WIDTH = 700;

const unsigned int CELL_SIZE_PIXELS = 128;
const unsigned int PARTING_LINE_SIZE_PIXELS = 8;

const sf::Vector2f ICONS_SCALE = sf::Vector2f(1.0f, 1.0f);

const sf::Vector2f FIELD_SIZE3_BUTTON_OFFSET = sf::Vector2f(WINDOW_WIDTH * -0.15f, WINDOW_HEIGHT * -0.3f);
const sf::Vector2f FIELD_SIZE5_BUTTON_OFFSET = sf::Vector2f(WINDOW_WIDTH * 0.15f, WINDOW_HEIGHT * -0.3f);

const sf::Vector2f MODE_PvP_BUTTON_OFFSET = sf::Vector2f(WINDOW_WIDTH * 0.3f, 0.0f);
const sf::Vector2f MODE_PvAI_BUTTON_OFFSET = sf::Vector2f(0.0f, 0.0f);
const sf::Vector2f MODE_AIvAI_BUTTON_OFFSET = sf::Vector2f(WINDOW_WIDTH * -0.3f, 0.0f);

const sf::Vector2f GAME_START_BUTTON_OFFSET = sf::Vector2f(0.0f, WINDOW_HEIGHT * 0.3f);
