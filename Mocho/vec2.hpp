#pragma once
#include <SFML/System/Vector2.hpp>
#include <math.h>
#include "math.hpp"
#include "definitions.hpp"


namespace mch{
using Vec2 = sf::Vector2f;
using Vec2i= sf::Vector2i;
using Vec2u= sf::Vector2u;

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



}
}
