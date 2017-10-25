/*
 * Button.cpp
 *
 *  Created on: Oct 24, 2017
 *      Author: santiago
 */

#include "Button.hpp"

namespace mch {
	void Button::press(bool pressed){
		m_just_updated = m_pressed!=pressed;
		m_pressed = pressed;
	};
	void Button::update(){
		m_just_updated = false;
	};

	void Button::clear(){
		m_pressed = false;
		m_just_updated = false;
	};

	bool Button::isPressed()const{return m_pressed;};
	bool Button::justUpdated()const{return m_just_updated;};



} /* namespace mch */
