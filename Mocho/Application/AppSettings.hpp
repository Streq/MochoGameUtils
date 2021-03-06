/*
 * AppSettings.hpp
 *
 *  Created on: Sep 22, 2017
 *      Author: santiago
 */

#pragma once
#include "Mocho/definitions.hpp"
#include "Mocho/vec2.hpp"
namespace mch{
struct AppSettings{
	static const AppSettings Default;
	bool frameskip;
	bool limit_framerate;
	uint64 microseconds_per_step;
	uint32 steps_per_render;

	Vec2u resolution;

};

}
