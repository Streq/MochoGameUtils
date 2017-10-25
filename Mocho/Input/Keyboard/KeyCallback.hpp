/*
 * Button.hpp
 *
 *  Created on: Oct 22, 2017
 *      Author: santiago
 */

#pragma once
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <Mocho/Input/ButtonCallback.hpp>
#include <functional>
namespace mch {


namespace Keyboard {


class KeyCallback : public ButtonCallback{
	public:
		void handle(const sf::Event& e);

		unsigned getKey()const;
		void setKey(sf::Keyboard::Key key);

	private:
		unsigned m_code;
};
}
} /* namespace mch */
