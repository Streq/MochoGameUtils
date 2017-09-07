/*
 * math.hpp
 *
 *  Created on: Aug 19, 2017
 *      Author: santiago
 */

#pragma once
#include <math.h>
#include <algorithm>
namespace mch{
	constexpr float PI = 3.14159265359f;


	//CONVERSION CONSTANTS
	static constexpr float D2R = (PI) / 180.f;
	static constexpr float R2D = 180.f / (PI);

	inline constexpr float degToRad(float deg){
		return deg*D2R;
	}
	inline constexpr float radToDeg(float rad){
		return rad*R2D;
	}

	inline float approach(float init, float target, float amount){
		float diff = target-init;
		float dir = copysignf(1.0f, diff);
		float abs_diff = copysignf(diff, 1.0f);
		float approached = init + dir*std::min(amount,abs_diff);

		return approached;
	}


}



