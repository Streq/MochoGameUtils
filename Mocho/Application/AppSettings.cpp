/*
 * AppSettings.cpp
 *
 *  Created on: Sep 23, 2017
 *      Author: santiago
 */

#include "AppSettings.hpp"


namespace mch{
const AppSettings AppSettings::Default{
	true,								//frameskip
	false,								//limit_framerate
	static_cast<uint64>(1e6/60),		//microseconds_per_step
	1,									//steps_per_render
	600,								//width
	400									//height
};

}
