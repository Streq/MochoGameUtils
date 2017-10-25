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
namespace mch {
namespace Joystick {
class ButtonCallback : public mch::ButtonCallback {
	public:
		void handle(const sf::Event& e);

		unsigned getButton()const;
		unsigned getJoystickId()const;

		void setButton(unsigned button, unsigned id);
		void setButton(unsigned button);
		void setJoystickId(unsigned id);
	private:
		unsigned m_code;
		unsigned m_joy_id;
};
} /* namespace Joystick */
} /* namespace mch */
