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
	while(!m_stack.isEmpty()){
		do{
			delta_time += clock.restart();
		}while(
			m_ctx.settings.limit_framerate &&
			delta_time.asMicroseconds() < m_ctx.settings.microseconds_per_step
		);

		input();

		do{
			//decrement delta_time or set it to 0 depending on frameskip
			delta_time = std::max
				( (delta_time-sf::microseconds(m_ctx.settings.microseconds_per_step))
					* static_cast<float>(m_ctx.settings.frameskip)
				, sf::Time::Zero
				)
			;
			update();
			++steps_since_last_render;
		}while(delta_time.asMicroseconds() > m_ctx.settings.microseconds_per_step);

		if(steps_since_last_render>= m_ctx.settings.steps_per_render){
			m_micros_since_last_render = render_clock.restart().asMicroseconds();
			draw();

		}
	}

}

void Application::init
		( std::unique_ptr<AppState> initState
		, AppSettings settings
		)
{
	m_ctx.settings = settings;
	m_ctx.window.create(
			sf::VideoMode(600,400),
			"Platform",sf::Style::Default);
	m_stack.pushState(std::move(initState));
}

void Application::input() {
	sf::Event e;
	while(m_ctx.window.pollEvent(e)){
		m_ctx.keyboard.handle(e);
		m_stack.input(e);
	}
}

void Application::update() {
	m_ctx.keyboard.update();
	m_stack.update();
}

void Application::draw() {
	m_ctx.window.clear();
	m_stack.draw(m_ctx.window,sf::RenderStates::Default);
	m_ctx.window.display();
}
Application::Application()
		: m_micros_since_last_render(0u)
{
	m_stack.setContext(this->m_ctx);
	m_ctx.keyboard.clear();
}

} /* namespace mch */


