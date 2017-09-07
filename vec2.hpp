#pragma once
#include <SFML/System/Vector2.hpp>
#include <math.h>
#include "math.hpp"
#include "definitions.hpp"


namespace mch{
namespace vec{

inline float dot(const Vec2& a, const Vec2& b){
	return a.x*b.x + a.y*b.y;
}

inline Vec2 scale(const Vec2& a, const Vec2& b){
	return Vec2(a.x * b.x, a.y * b.y);
}

inline float cross(const Vec2& a,const Vec2& b){
	return a.x*b.y - a.y*b.x;
}

inline float square_length(const Vec2& a){return a.x*a.x+a.y*a.y;}

inline float length(const Vec2& a){return sqrt(a.x*a.x+a.y*a.y);}

inline Vec2 normalized(const Vec2& a){
	auto len=length(a);
	if (len>mch::epsilon)
		return a/len;
	return Vec2(0.f,0.f);
}

inline Vec2 rotate(const Vec2& v, float angle){
		float s = sin(angle);
		float c = cos(angle);
		return Vec2(v.x * c - v.y * s, v.x * s + v.y * c);
}

inline Vec2 rotateWithPivot(const Vec2& v, const Vec2 pivot, float angle){
	auto ret = v-pivot;
	rotate(ret,angle);
	return ret+pivot;
}

inline float getAngleInRads(const Vec2& v){
	return atan2(v.x,v.y);
}

inline Vec2 fromAngleinRads(float rads){
	return Vec2(cos(rads),sin(rads));
}

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

Intersection findIntersection
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
	auto cross_r_s = cross(r,s);
	if(!cross_r_s)return i;
	i.t = cross(q_min_p, s) / cross_r_s;
	i.u = cross(q_min_p, r) / cross_r_s;

	i.exists = 0.f <= i.t && i.t <= 1.f
			&& 0.f <= i.u && i.u <= 1.f;
	return i;

}


}
}
