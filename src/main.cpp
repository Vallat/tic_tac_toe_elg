#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "StateMachine.h"


int main()
{
	Renderer* renderer = Renderer::get_renderer();

	StateMachine* state_machine = new StateMachine;

	renderer->get_window()->setFramerateLimit(30);

	while (renderer->get_window()->isOpen())
	{
		sf::Event event;
		while (renderer->get_window()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				renderer->get_window()->close();
		}

		renderer->window_clear();
		state_machine->process();
		renderer->window_display();
	}
}
