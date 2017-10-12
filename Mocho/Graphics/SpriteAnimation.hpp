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
#include "Mocho/Graphics/SpriteGallery.hpp"

namespace sf{
class Texture;
class Time;
}
namespace mch {

class SpriteAnimation {
	public:
		void update(sf::Time time);

		const sf::Sprite& getCurrentFrame()const;

		void setSpriteGallery(const SpriteGallery& gallery);

		void setIndex(int n);
		void resetElapsedTime();

		void setFrameTime(sf::Time frameTime);

	private:
		const SpriteGallery* m_gallery = nullptr;
		sf::Time m_elapsed_time = sf::Time::Zero;
		sf::Time m_frame_time = sf::Time::Zero;
		int m_current_index = 0;
};

} /* namespace mch */
