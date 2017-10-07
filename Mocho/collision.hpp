/*
 * collision.hpp
 *
 *  Created on: Sep 14, 2017
 *      Author: santiago
 */

#pragma once
#include "vec2.hpp"

namespace mch{





struct AABB{
	Vec2f topleft;
	Vec2f size;
};


namespace collision{

inline bool line_line
( const Vec2f& a
, const Vec2f& b
, const Vec2f& c
, const Vec2f& d
, Vec2f& intersection
){
	//t = (q − p) x s / (r x s)
	//u = (q − p) x r / (r x s)

	//hay interseccion si r x s != 0 and 0 <= t <= 1 and 0 <= u <= 1
	bool exists=false;
	auto b_minus_a = b-a;
	auto d_minus_c = c-b;
	auto c_min_a = c-a;
	auto cross_r_s = vec::cross(b_minus_a,d);
	if(!cross_r_s)return false;
	float t = vec::cross(c_min_a, d_minus_c) / cross_r_s;
	float u = vec::cross(c_min_a, b_minus_a) / cross_r_s;

	exists =  0.f <= t && t <= 1.f
		&& 0.f <= u && u <= 1.f;
	intersection = a+(b_minus_a*t);
	return exists;

}

/* Find an intersection between segments ab1 and ab2.
 * @returns wether there's an intersection or not
*/

inline bool line_line
( const Vec2f& a
, const Vec2f& b
, const Vec2f& c
, const Vec2f& d
){
	Vec2f intersection{};
	return line_line(a,b,c,d,intersection);
}


inline bool aabb_aabb(const AABB& a, const AABB& b){
	return  !( a.topleft.x > b.topleft.x + b.size.x
			|| b.topleft.x > a.topleft.x + a.size.x
			|| a.topleft.y > b.topleft.y + b.size.y
			|| b.topleft.y > a.topleft.y + a.size.y
			);
}

inline bool aabb_aabb(const Vec2f& lt1, const Vec2f& wl1, const Vec2f& lt2, const Vec2f& wl2){
	return  !( lt1.x > lt2.x + wl2.x
			|| lt2.x > lt1.x + wl1.x
			|| lt1.y > lt2.y + wl2.y
			|| lt2.y > lt1.y + wl1.y
			);
}

inline bool circle_circle(const Vec2f& pos1, float32 rad1, const Vec2f& pos2, float32 rad2){
	auto dist = rad1+rad2;
	return vec::square_length(pos2-pos1) < dist*dist;
}


}


}



