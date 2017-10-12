/*
 * SpriteAnimation.cpp
 *
 *  Created on: Oct 11, 2017
 *      Author: santiago
 */

#include "Mocho/Graphics/SpriteAnimation.hpp"

namespace mch{

const sf::Sprite&
SpriteAnimation::getCurrentFrame() const{
	return m_gallery->getFrame(m_current_index);
}

void SpriteAnimation::setSpriteGallery(
		const SpriteGallery& gallery) {
	m_gallery=&gallery;
}

void SpriteAnimation::update(
		sf::Time dt) {
	m_elapsed_time += dt;

	if(m_elapsed_time >= m_frame_time){
		int index_dif = static_cast<int>(m_elapsed_time/m_frame_time);
		m_current_index += index_dif;
		m_elapsed_time %= m_frame_time;
	}
}



void SpriteAnimation::setIndex(
		int n) {
	m_current_index = n;
}

void SpriteAnimation::resetElapsedTime() {
	m_elapsed_time=sf::Time::Zero;
}


void SpriteAnimation::setFrameTime(
		sf::Time frameTime) {
	m_frame_time = frameTime;
}

}
