/*
 * Button.cpp
 *
 *  Created on: Oct 22, 2017
 *      Author: santiago
 */

#include "ButtonCallback.hpp"

namespace mch {
namespace Joystick {
void ButtonCallback::handle(const sf::Event& e){
	auto code = e.joystickButton.button;
	auto id = e.joystickButton.joystickId;
	auto type = e.type;
	if(code == m_code && id == m_joy_id){
		switch (type){
			case sf::Event::EventType::JoystickButtonPressed:{
				press(true);
			}break;
			case sf::Event::EventType::JoystickButtonReleased:{
				press(false);
			}break;
		}
	}
};


unsigned ButtonCallback::getButton()const {return m_code;};
unsigned ButtonCallback::getJoystickId()const {return m_joy_id;}

void ButtonCallback::setButton(unsigned button, unsigned id){m_code = button; m_joy_id = id;};
void ButtonCallback::setButton(unsigned button){m_code = button;}
void ButtonCallback::setJoystickId(unsigned id){m_joy_id = id;}


} /* namespace Joystick */
} /* namespace mch */


