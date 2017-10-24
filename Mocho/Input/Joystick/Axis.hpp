/*
 * Axis.hpp
 *
 *  Created on: Oct 24, 2017
 *      Author: santiago
 */

#pragma once
#include <SFML/Window/Joystick.hpp>
namespace mch {
namespace Joystick {

struct Axis {
	public:
		using ID = sf::Joystick::Axis;
		void check(ID axis, float position);
	public:
		ID m_id;
		float m_position;


};

} /* namespace Joystick */
} /* namespace mch */
