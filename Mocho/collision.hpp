/*
 * collision.hpp
 *
 *  Created on: Sep 14, 2017
 *      Author: santiago
 */

#pragma once
#include "vec2.hpp"

namespace mch{
struct Intersection{
	bool exists;
	float t,u;
};

/* Find an intersection between segments p to (p+r) and q to (q+s).
 * The boolean exists determines whether there's a certain (single)
 * 	point of intersection.
 * You can calculate the exact point of intersection
 *  by multiplying r by t and adding it to p
 *  or by multiplying s by u and adding it to q
 * */

inline Intersection findIntersection
( const Vec2& p
, const Vec2& r
, const Vec2& q
, const Vec2& s
){
	//t = (q − p) x s / (r x s)
	//u = (q − p) x r / (r x s)

	//hay interseccion si r x s != 0 and 0 <= t <= 1 and 0 <= u <= 1

	Intersection i;
	i.exists = false;
	auto q_min_p = q-p;
	auto cross_r_s = vec::cross(r,s);
	if(!cross_r_s)return i;
	i.t = vec::cross(q_min_p, s) / cross_r_s;
	i.u = vec::cross(q_min_p, r) / cross_r_s;

	i.exists = 0.f <= i.t && i.t <= 1.f
			&& 0.f <= i.u && i.u <= 1.f;
	return i;

}

struct AABB{
	Vec2 topleft;
	Vec2 size;
};

inline bool collisionAABB(const AABB& a, const AABB& b){
	return  !( a.topleft.x > b.topleft.x + b.size.x
			|| b.topleft.x > a.topleft.x + a.size.x
			|| a.topleft.y > b.topleft.y + b.size.y
			|| b.topleft.y > a.topleft.y + a.size.y
			);
}

inline bool collisionAABB(const Vec2& lt1, const Vec2& wl1, const Vec2& lt2, const Vec2& wl2){
	return  !( lt1.x > lt2.x + wl2.x
			|| lt2.x > lt1.x + wl1.x
			|| lt1.y > lt2.y + wl2.y
			|| lt2.y > lt1.y + wl1.y
			);
}

inline bool collisionCircle(const Vec2& pos1, float32 rad1, const Vec2& pos2, float32 rad2){
	auto dist = rad1+rad2;
	return vec::square_length(pos2-pos1) < dist*dist;
}

}



