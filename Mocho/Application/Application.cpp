/*
 * Application.cpp
 *
 *  Created on: Sep 22, 2017
 *      Author: santiago
 */

#include "Application.hpp"
namespace mch {


void Application::run() {
	Time delta_time=Time::Zero;
	Clock clock;
	Clock render_clock;
	int32 steps_since_last_render = 0;
	while(window.isOpen()){
		do{
			delta_time += clock.restart();
		}while(settings.limit_framerate && delta_time.asMicroseconds() < settings.microseconds_per_step);

		input();

		do{
			//decrement delta_time or set it to 0 depending on frameskip
			delta_time = std::max
				( (delta_time-settings.microseconds_per_step)*static_cast<float>(settings.frameskip)
				, sf::Time::Zero
				)
			;
			update();
			++steps_since_last_render;
		}while(delta_time > settings.microseconds_per_step);

		if(steps_since_last_render>=settings.steps_per_render){
			micros_since_last_render = render_clock.restart().asMicroseconds();
			draw();

		}
	}

}

void Application::init() {
}

void Application::input() {
	sf::Event e;
	while(window.pollEvent(e)){
		stack.input(e);
	}
}

void Application::update() {
	stack.update();
}

void Application::draw() {
	stack.draw(window,sf::RenderStates::Default);
}

} /* namespace mch */

mch::Application::Application() {
}
