/*
 * SpriteAnimation.hpp
 *
 *  Created on: Sep 26, 2017
 *      Author: santiago
 */

#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "Mocho/vec2.hpp"

#include <SFML/System/Time.hpp>
namespace sf{
class Texture;
class Time;
}
namespace mch {

class SpriteAnimation {
	public:
		enum class Type{
			Once,
			Loop,
			BackAndForth,
		};

		SpriteAnimation();
		SpriteAnimation(const sf::Texture*, Vec2u frameSize, int32 begin=0, int32 end=0);

		void update(sf::Time dt);

		sf::Time getFrameDuration()const;

		/*Use negative values in @frames to go backwards*/
		void setFrameSpeed(sf::Time dt,int frames);
		void setAnimationType(Type t);

		Type getAnimationType()const;

		sf::Sprite& getSprite();
		const sf::Sprite& getSprite()const;



	private:
		void advanceIndex(int n);
		void advanceIndex();
	private:
		sf::Sprite m_sprite;
		Vec2u m_frameSize;
		Type m_type;
		int32 m_begin;
		int32 m_frames;
		int32 m_index;
		Vec2u m_dimensions;
		sf::Time m_frameDuration;
		sf::Time m_elapsedTime;
		bool m_orientation;
};

} /* namespace mch */
