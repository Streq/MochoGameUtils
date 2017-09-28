#pragma once
#include <SFML/System/Vector2.hpp>
#include <math.h>
#include "math.hpp"
#include "definitions.hpp"


namespace mch{

template<typename T>
using Vec2 = sf::Vector2<T>;

using Vec2f = sf::Vector2f;
using Vec2i= sf::Vector2i;
using Vec2u= sf::Vector2u;

namespace vec{

template<typename T>
inline T dot(const Vec2<T>& a, const Vec2<T>& b){
	return a.x*b.x + a.y*b.y;
}

template<typename T>
inline Vec2<T> scale(const Vec2<T>& a, const Vec2<T>& b){
	return Vec2f(a.x * b.x, a.y * b.y);
}



template<typename T>
inline T cross(const Vec2<T>& a,const Vec2<T>& b){
	return a.x*b.y - a.y*b.x;
}

template<typename T>
inline T square_length(const Vec2<T>& a){return a.x*a.x+a.y*a.y;}

template<typename T>
inline float length(const Vec2<T>& a){return sqrt(a.x*a.x+a.y*a.y);}

template<typename T>
inline Vec2<T> normalized(const Vec2<T>& a){
	auto len=length<T>(a);
	if (len>mch::epsilon)
		return a/len;
	return Vec2<T>(0.f,0.f);
}

template<typename T>
inline Vec2f rotate(const Vec2<T>& v, float angle){
		float s = sin(angle);
		float c = cos(angle);
		return Vec2f(v.x * c - v.y * s, v.x * s + v.y * c);
}

template<typename T>
inline Vec2f rotateWithPivot(const Vec2<T>& v, const Vec2<T> pivot, float angle){
	auto ret = v-pivot;
	rotate<T>(ret,angle);
	return ret+pivot;
}

template<typename T>
inline float getAngleInRads(const Vec2<T>& v){
	return atan2(v.x,v.y);
}

inline Vec2f fromAngleinRads(float rads){
	return Vec2f(cos(rads),sin(rads));
}



}
}
