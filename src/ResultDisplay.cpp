#include "ResultDisplay.h"
#include "Globals.h"
#include "Renderer.h"
#include "FieldCell.h"

ResultDisplay*  ResultDisplay::result_display_ = nullptr;

ResultDisplay* ResultDisplay::get_instance()
{
	if (result_display_ == nullptr)
	{
		result_display_ = new ResultDisplay();
	}
	return result_display_;
}


ResultDisplay::ResultDisplay()
{
	if (!loaded_font.loadFromFile("Resources/Roboto-Black.ttf"))
	{
		throw std::runtime_error("ResultDisplay: Didn't manage to load font file!");
	}
	timer = new sf::Clock();

	displayed_text = new sf::Text;
	displayed_text->setFont(loaded_font);
	displayed_text->setCharacterSize(TEXT_SIZE);
	displayed_text->setFillColor(sf::Color(180, 255, 180));
	displayed_text->setOutlineColor(sf::Color(80, 230, 80));
	displayed_text->setOutlineThickness(2.0f);
	displayed_text->setString("");
}


bool ResultDisplay::process()
{
	if (timer->getElapsedTime() > sf::seconds(SECONDS_TO_DISPLAY_RESULT))
	{
		displayed_text->setString("");
		return false;
	};
	return true;
}


void ResultDisplay::send_render_information()
{
	if (displayed_text->getString() == "")
	{
		return;
	}
	if (win_line != nullptr)
	{
		Renderer::get_renderer()->window_draw(*win_line);
	}
	Renderer::get_renderer()->window_draw(*displayed_text);
}


void ResultDisplay::set_up_win_result(WIN_RESULT win_result)
{
	switch (win_result)
	{
	case WIN_RESULT::CROSS_WIN:
		displayed_text->setString("X's won!");
		break;
	case WIN_RESULT::ZERO_WIN:
		displayed_text->setString("O'x won!");
		break;
	case WIN_RESULT::DRAFT:
		displayed_text->setString("Draft!");
		break;
	}
	sf::FloatRect text_rect = displayed_text->getLocalBounds();
	displayed_text->setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
	displayed_text->setPosition(Renderer::get_renderer()->get_window()->getView().getCenter());
	timer->restart();
}


void ResultDisplay::draw_win_line(std::vector<FieldCell*> win_line_)
{
	sf::Vector2f line_start = win_line_[0]->get_cell_center_pos();
	sf::Vector2f line_end = win_line_[win_line_.size() - 1]->get_cell_center_pos();

	sf::RectangleShape* line = new sf::RectangleShape(sf::Vector2f(line_start.x - line_end.x + WIN_LINE_THICKNESS, line_start.y - line_end.y + WIN_LINE_THICKNESS));
	line->setPosition(sf::Vector2f(line_end.x - WIN_LINE_THICKNESS / 2, line_end.y - WIN_LINE_THICKNESS / 2));
	line->setFillColor(sf::Color(80, 80, 240));
	line->setOutlineThickness(WIN_LINE_THICKNESS / 5);
	line->setOutlineColor(sf::Color(40, 40, 200));
	win_line = line;
}

void ResultDisplay::clear_win_line()
{
	win_line = nullptr;
}
