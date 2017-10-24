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
namespace mch {
namespace Keyboard {
class Button {
	public:
		void handle(const sf::Event& e);
		bool isPressed()const;
		bool isJustUpdated()const;
		unsigned getButton()const;
		void setKey(sf::Keyboard::Key key);

		void clear();
		void update(bool pressed);
	private:
		unsigned m_code;
		bool m_pressed;
		bool m_just_updated;
};
}
} /* namespace mch */
