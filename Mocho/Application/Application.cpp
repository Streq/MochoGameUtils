/*
 * Application.cpp
 *
 *  Created on: Sep 22, 2017
 *      Author: santiago
 */

#include "Application.hpp"
#include <utility>
#include "Mocho/time.hpp"
#include <SFML/Window/Event.hpp>

#include "Mocho/Application/AppSettings.hpp"
#include "Mocho/Application/AppState.hpp"

namespace mch {


void Application::run() {
	Time delta_time=Time::Zero;
	Clock clock;
	Clock render_clock;
	int32 steps_since_last_render = 0;
	while(ctx.window.isOpen()){
		do{
			delta_time += clock.restart();
		}while(
			ctx.settings.limit_framerate &&
			delta_time.asMicroseconds() < ctx.settings.microseconds_per_step
		);

		input();

		do{
			//decrement delta_time or set it to 0 depending on frameskip
			delta_time = std::max
				( (delta_time-sf::microseconds(ctx.settings.microseconds_per_step))
					* static_cast<float>(ctx.settings.frameskip)
				, sf::Time::Zero
				)
			;
			update();
			++steps_since_last_render;
		}while(delta_time.asMicroseconds() > ctx.settings.microseconds_per_step);

		if(steps_since_last_render>= ctx.settings.steps_per_render){
			micros_since_last_render = render_clock.restart().asMicroseconds();
			draw();

		}
	}

}

void Application::init
		( std::unique_ptr<AppState> initState
		, AppSettings settings
		)
{
	this->ctx.settings = settings;
	stack.setContext(ctx);
	stack.pushState(std::move(initState));


}

void Application::input() {
	sf::Event e;
	while(ctx.window.pollEvent(e)){
		stack.input(e);
	}
}

void Application::update() {
	stack.update();
}

void Application::draw() {
	stack.draw(ctx.window,sf::RenderStates::Default);
}
Application::Application()
		: micros_since_last_render(0u)
{
	stack.setContext(this->ctx);
}

} /* namespace mch */


