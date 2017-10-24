/*
 * Deadzone.hpp
 *
 *  Created on: Oct 23, 2017
 *      Author: santiago
 */

#pragma once
#include <Mocho/vec2.hpp>
namespace mch {
namespace Joystick {

	struct DeadZone{
		public:
			Vec2f handle(Vec2f input)const;

		public:
			//square dead_zone for x axis
			float m_dead_zone_x;

			//square dead_zone for y axis
			float m_dead_zone_y;

			//radius of the deadzone circle
			float m_dead_zone_circle;

			//determines the amount of directions, 0 means as many as possible
			//pi*2/n means n directions
			float m_dead_zone_angle_range;

	};

} /* namespace Joystick */
} /* namespace mch */
