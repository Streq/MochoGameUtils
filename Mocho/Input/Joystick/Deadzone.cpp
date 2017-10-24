/*
 * Deadzone.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: santiago
 */

#include "Deadzone.hpp"
#include <Mocho/vec2.hpp>

namespace mch {
namespace Joystick {

Vec2f DeadZone::handle(Vec2f input) const {
	if(copysign(input.x,1.f) < m_dead_zone_x){
		input.x = 0.f;
	}
	if(copysign(input.y,1.f) < m_dead_zone_y){
		input.y = 0.f;
	}

	if(m_dead_zone_circle > 0.f){
		if(vec::square_length(input)<m_dead_zone_circle){
			input.x=0.f;
			input.y=0.f;
		}
	}

	if(m_dead_zone_angle_range > 0.f){
		auto angle = vec::getAngleInRads(input);
		int slice = angle / (m_dead_zone_angle_range);
		if(slice%2)++slice;
		input = vec::fromAngleinRads(slice*m_dead_zone_angle_range)*vec::length(input);
	}
	return input;
}




} /* namespace Joystick */
} /* namespace mch */
