/*
 * Button.cpp
 *
 *  Created on: Oct 22, 2017
 *      Author: santiago
 */

#include "Button.hpp"

namespace mch {
namespace Joystick {
void Button::handle(const sf::Event& e){
	auto code = e.joystickButton.button;
	auto id = e.joystickButton.joystickId;
	auto type = e.type;
	if(code == m_code && id == m_id){
		switch (type){
			case sf::Event::EventType::JoystickButtonPressed:{
				update(true);
			}break;
			case sf::Event::EventType::JoystickButtonReleased:{
				update(false);
			}break;
		}
	}
};

bool Button::isPressed()const {return m_pressed;};
bool Button::isJustUpdated()const {return m_just_updated;};

unsigned Button::getButton()const {return m_code;};
unsigned Button::getJoystickId()const {return m_id;}

void Button::setButton(unsigned button, unsigned id){m_code = button; m_id = id;};
void Button::setButton(unsigned button){m_code = button;}
void Button::setJoystickId(unsigned id){m_id = id;}

void Button::update(bool pressed){
	m_just_updated = (pressed!=m_pressed);
	m_pressed = pressed;
}

void Button::clear() {
	m_just_updated=false;
	m_pressed=false;
}

} /* namespace Joystick */
} /* namespace mch */


