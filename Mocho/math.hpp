/*
 * math.hpp
 *
 *  Created on: Aug 19, 2017
 *      Author: santiago
 */

#pragma once
#include <math.h>
#include <algorithm>
#include <functional>
#include <cassert>
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

	template<typename T>
	inline T sign(T x){
		return (T)((x > (T)0) - (x < (T)0));
	}

	template<class T, class Compare>
	constexpr const T& clamp( const T& v, const T& lo, const T& hi, Compare comp ){
		return assert( !comp(hi, lo) ),
			comp(v, lo) ? lo : comp(hi, v) ? hi : v;
	}

	template<class T>
	constexpr const T& clamp( const T& v, const T& lo, const T& hi ){
		return clamp( v, lo, hi, std::less<T>() );
	}

	template<typename T>
	inline T approach(T init, T target, T amount){
		T diff = target-init;
		T dir = sign(diff);
		T abs_diff = diff*sign(diff);
		T approached = init + dir*std::min(amount,abs_diff);
		return approached;
	}

	template<>
	inline float approach(float init, float target, float amount){
		float diff = target-init;
		float dir = copysignf(1.0f, diff);
		float abs_diff = copysignf(diff, 1.0f);
		float approached = init + dir*std::min(amount,abs_diff);
		return approached;
	}


}



