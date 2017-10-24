/*
 * Stick.hpp
 *
 *  Created on: Oct 22, 2017
 *      Author: santiago
 */

#pragma once
#include <Mocho/math.hpp>
#include <Mocho/vec2.hpp>
#include <SFML/Window/Event.hpp>

#include <Mocho/Input/Joystick/Axis.hpp>
#include <Mocho/Input/Joystick/Deadzone.hpp>
namespace mch {
namespace Joystick {

class Stick {
	public:
		void handle(const sf::Event& e);

		Vec2f getRawPosition()const;
		Vec2f getPosition()const;

		void setJoyId(unsigned id){m_joy_id=id;}
		void setXAxis(unsigned axis_id){m_x.m_id=(Axis::ID)axis_id;}
		void setYAxis(unsigned axis_id){m_y.m_id=(Axis::ID)axis_id;}
	private:

		unsigned m_joy_id;
		Axis m_x;
		Axis m_y;
		DeadZone m_deadzone;
};

} /* namespace Joystick */
} /* namespace mch */
