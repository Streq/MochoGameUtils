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
namespace Joystick {
class Button {
	public:
		void handle(const sf::Event& e);
		bool isPressed()const;
		bool isJustUpdated()const;
		unsigned getButton()const;
		unsigned getJoystickId()const;
		void setButton(unsigned button, unsigned id);
		void setButton(unsigned button);
		void setJoystickId(unsigned id);

		void clear();
		void update(bool pressed);

	private:
		unsigned m_code;
		unsigned m_id;
		bool m_pressed;
		bool m_just_updated;
};
} /* namespace Joystick */
} /* namespace mch */
