/*
 * collision.hpp
 *
 *  Created on: Sep 14, 2017
 *      Author: santiago
 */

#pragma once
#include "Mocho/vec2.hpp"

namespace mch{


struct AABB{
	Vec2f topleft;
	Vec2f size;
};
struct Circle{
	Vec2f center;
	float32 radius;
};

enum class ShapeType{
	AABB,
	Circle
};


struct RigidBody;
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
	auto c_minus_a = c-a;
	auto cross_r_s = vec::cross(b_minus_a,d);
	if(!cross_r_s)return false;
	float t = vec::cross(c_minus_a, d_minus_c) / cross_r_s;
	float u = vec::cross(c_minus_a, b_minus_a) / cross_r_s;

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

	return
	// If...
	// a's left is not to the right of b's right
	!( a.topleft.x > b.topleft.x + b.size.x

	// and b's left is not to the right of a's right
	|| b.topleft.x > a.topleft.x + a.size.x

	// and a's top is not below b's bot
	|| a.topleft.y > b.topleft.y + b.size.y

	// and b's top is not below b's bot
	|| b.topleft.y > a.topleft.y + a.size.y

	// then an intersection happens
	);

}

inline bool aabb_aabb(const AABB& a, const AABB& b, AABB& intersection){
	Vec2f topleft{
		std::max(a.topleft.x, b.topleft.x),
		std::max(a.topleft.y, b.topleft.y)
	};
	Vec2f botright{
		std::min(a.topleft.x+a.size.x, b.topleft.x+b.size.x),
		std::min(a.topleft.y+a.size.y, b.topleft.y + b.size.y)
	};
	intersection.topleft = topleft;
	intersection.size = botright-topleft;
	return intersection.size.x > 0.f && intersection.size.y > 0.f;
}



inline bool circle_circle(const Circle& cir1, const Circle& cir2){
	// Calculate distance between centers
	auto dist = cir1.radius+cir2.radius;

	// If the distance between centers is less than the sum of the circles' radiuses,
	// an intersection occurs
	return vec::square_length(cir1.center-cir2.center) < dist*dist;
}

inline bool aabb_circle(const AABB& aabb, const Circle& cir){
	// Find the closest point to the circle within the rectangle
	// Assumes axis alignment! ie rect must not be rotated
	auto closestX = mch::clamp(cir.center.x, aabb.topleft.x, aabb.topleft.x + aabb.size.x);
	auto closestY = mch::clamp(cir.center.y, aabb.topleft.y, aabb.topleft.y + aabb.size.y);

	// Calculate the distance between the circle's center and this closest point
	auto distanceX = cir.center.x - closestX;
	auto distanceY = cir.center.y - closestY;

	// If the distance is less than the circle's radius, an intersection occurs
	auto distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
	return distanceSquared < (cir.radius * cir.radius);
}

class CollisionManager{
	public:
		struct Collision{
			RigidBody* a;
			RigidBody* b;
			//Vec2f global_point;
		};

	private:
		std::vector<Circle> m_circles;
		std::vector<AABB> m_aabbs;

};

}


}



