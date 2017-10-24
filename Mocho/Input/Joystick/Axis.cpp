/*
 * Axis.cpp
 *
 *  Created on: Oct 24, 2017
 *      Author: santiago
 */

#include "Axis.hpp"

namespace mch {
namespace Joystick {

void Axis::check(ID axis, float position){
	if(axis==m_id) m_position=position;
}
} /* namespace Joystick */
} /* namespace mch */
