/*
 * AppState.hpp
 *
 *  Created on: Sep 22, 2017
 *      Author: santiago
 */

#pragma once

namespace sf{
struct Event;
struct RenderTarget;
struct RenderStates;
}

namespace mch {
class AppStack;
struct AppSettings;

class AppState {
	public:
		virtual ~AppState();

		virtual bool update();
		virtual bool draw(sf::RenderTarget& target, sf::RenderStates states)const;
		virtual bool input(const sf::Event& event);

	protected:
		AppStack* stack;
		AppSettings* settings;
};

} /* namespace mch */
