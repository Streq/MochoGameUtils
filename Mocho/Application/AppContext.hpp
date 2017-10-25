/*
 * AppContext.hpp
 *
 *  Created on: Sep 23, 2017
 *      Author: santiago
 */

#pragma once

#include "Mocho/Application/AppSettings.hpp"
#include "Mocho/Application/AppStack.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

#include <Mocho/Input/Keyboard/State.hpp>

namespace sf{
class RenderWindow;
}

namespace mch{

struct AppContext{
	sf::RenderWindow window;
	AppSettings settings;
	Keyboard::State keyboard;
};


}
