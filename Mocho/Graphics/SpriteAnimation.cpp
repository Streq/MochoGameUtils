/*
 * SpriteIndex.cpp
 *
 *  Created on: Sep 26, 2017
 *      Author: santiago
 */

#include "SpriteAnimation.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <algorithm>
namespace mch {


SpriteAnimation::SpriteAnimation()
	: m_sprite()
	, m_index(0)
	, m_frameSize(0u,0u)
	, m_type(Type::Once)
	, m_begin(0)
	, m_frames(0)
	, m_dimensions(0,0)
	, m_frameDuration(sf::Time::Zero)
	, m_elapsedTime(sf::Time::Zero)
	, m_orientation(true)

{

}

SpriteAnimation::SpriteAnimation(
		const sf::Texture* texture
		,Vec2u m_frameSize
		,int32 begin
		,int32 frames)
	: m_sprite()
	, m_frameSize(m_frameSize)
	, m_type(Type::Once)
	, m_begin(begin)
	, m_frames(frames)
	, m_index(begin)
	, m_dimensions(0,0)
	, m_frameDuration(sf::Time::Zero)
	, m_elapsedTime(sf::Time::Zero)
	, m_orientation(true)
{
	m_sprite.setTexture(*texture);
	m_sprite.setTextureRect(sf::IntRect(0,0,m_frameSize.x,m_frameSize.y));
	auto texSize = texture->getSize();
	m_dimensions.x = texSize.x/m_frameSize.x;
	m_dimensions.y = texSize.y/m_frameSize.y;
	if(!m_frames)m_frames=m_dimensions.x*m_dimensions.y;

}


void SpriteAnimation::update(
		sf::Time dt) {
	if(m_frameDuration == sf::Time::Zero)
		return;
	m_elapsedTime+=dt;
	int framesToAdvance=0;
	while(m_elapsedTime>=m_frameDuration){
		m_elapsedTime-=m_frameDuration;
		advanceIndex();
		//++framesToAdvance;
	}
	//advanceIndex(framesToAdvance);
	Vec2u iVec
		(m_index%m_dimensions.x
		,m_index/m_dimensions.x);
	m_sprite.setTextureRect
			(sf::IntRect
				(m_frameSize.x*iVec.x
				,m_frameSize.y*iVec.y
				,m_frameSize.x
				,m_frameSize.y));

}

sf::Time SpriteAnimation::getFrameDuration() const {
	return m_frameDuration;
}

void SpriteAnimation::setFrameSpeed(
		sf::Time dt, int frames) {
	if(frames)
		m_frameDuration = dt/(sf::Int64)abs(frames);
	else
		m_frameDuration = sf::Time::Zero;
	m_orientation = frames*dt.asMilliseconds()>=0;
}

sf::Sprite& SpriteAnimation::getSprite() {
	return m_sprite;
}

const sf::Sprite& SpriteAnimation::getSprite() const {
	return m_sprite;
}

void SpriteAnimation::advanceIndex(int n) {
	int sign = 2*m_orientation-1;
	m_index += n*sign;
	if(m_index>=m_frames||m_index<0){
		switch(m_type){
			case Type::Once:{
				m_index = clamp(m_index,0,m_frames-1);
			}break;
			case Type::Loop:{
				m_index = (m_index%m_frames + m_frames)%m_frames;
			}break;
			case Type::BackAndForth:{
				bool odd_loop = !((m_index/m_frames)%2);
				int looped_index = (m_index%m_frames + m_frames)%m_frames;
				m_index = (odd_loop*m_frames-(2*odd_loop-1)*looped_index);
			}break;
		}
	}
}

void SpriteAnimation::advanceIndex() {
	m_index += 2*m_orientation-1;
	if(m_index>=m_frames||m_index<=-1){
		switch(m_type){
			case Type::Once:{
				m_index = clamp(m_index,0,m_frames-1);
			}break;
			case Type::Loop:{
				m_index = (m_index + m_frames) % m_frames;
			}break;
			case Type::BackAndForth:{
				m_orientation = !m_orientation;
				m_index += 2*(2*m_orientation-1);

			}break;
		}
	}
}

void SpriteAnimation::setAnimationType(
		Type t) {
	m_type=t;
}

SpriteAnimation::Type SpriteAnimation::getAnimationType() const {
	return m_type;
}

} /* namespace mch */


