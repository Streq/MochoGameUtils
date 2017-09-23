/*
 * Application.hpp
 *
 *  Created on: Sep 22, 2017
 *      Author: santiago
 */

#pragma once

#include "Mocho/definitions.hpp"
#include "Mocho/Application/AppSettings.hpp"
#include "Mocho/Application/AppStack.hpp"


#include <SFML/Graphics/RenderWindow.hpp>

namespace mch {
class AppState;

class Application {
	public:

		Application();
		void init(std::unique_ptr<AppState> initState);
		void run();

		void input();
		void update();
		void draw();



	private:
		sf::RenderWindow window;
		AppSettings settings;
		AppStack stack;

		int64 micros_since_last_render;

};

} /* namespace mch */
