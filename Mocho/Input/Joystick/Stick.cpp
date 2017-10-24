/*
 * Stick.cpp
 *
 *  Created on: Oct 22, 2017
 *      Author: santiago
 */

#include "Stick.hpp"

namespace mch {
namespace Joystick {

void Stick::handle(const sf::Event& e){
	switch(e.type){
		case sf::Event::EventType::JoystickMoved:{
			auto id = e.joystickMove.joystickId;
			if(id==m_joy_id){
				auto axis = e.joystickMove.axis;
				auto position = e.joystickMove.position;
				m_x.check(axis,position);
				m_y.check(axis,position);
			}
		}break;
	}
}


Vec2f Stick::getPosition()const{return m_deadzone.handle(getRawPosition());};
Vec2f Stick::getRawPosition()const{return Vec2f(m_x.m_position,m_y.m_position);};


} /* namespace Joystick */
} /* namespace mch */
