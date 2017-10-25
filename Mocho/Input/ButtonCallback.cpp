/*
 * ButtonCallback.cpp
 *
 *  Created on: Oct 24, 2017
 *      Author: santiago
 */

#include "ButtonCallback.hpp"

namespace mch {

void ButtonCallback::update(){
	if(this->isPressed() && this->justUpdated() && m_pressed_callback){
		m_pressed_callback();
	}
	if(!this->isPressed() && this->justUpdated() && m_released_callback){
		m_released_callback();
	}
	if(this->isPressed() && m_hold_down_callback){
		m_hold_down_callback();
	}
	this->Button::update();
}

void ButtonCallback::setOnPressed(
		std::function<void(void)> callback) {
	m_pressed_callback=callback;
}

void ButtonCallback::setOnReleased(
		std::function<void(void)> callback) {
	m_released_callback=callback;
}

void ButtonCallback::setHoldDown(
		std::function<void(void)> callback) {
	m_hold_down_callback = callback;
}



} /* namespace mch */

