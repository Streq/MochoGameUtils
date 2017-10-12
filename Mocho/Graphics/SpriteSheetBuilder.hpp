/*
 * SpriteSheetReader.hpp
 *
 *  Created on: Oct 11, 2017
 *      Author: santiago
 */

#pragma once

#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
namespace mch {

class SpriteSheetBuilder {
	public:
		std::vector<sf::Sprite> makeSheet(const sf::Texture& texture);

		void setFrames(unsigned frames);
		void setSize(const sf::Vector2u& size);
		void setHorizontalRead(bool);
		void setIndex(sf::Vector2i index);
		void setReadForward(bool);
		void setReturnForward(bool);

	private:
		sf::Vector2u 			m_frame_size;

		sf::Vector2i 			m_index = {0,0};

		//zero means all
		int 					m_frames = 0;

		bool 					m_horizontal_read = true;
		bool 					m_positive_read = true;
		bool 					m_positive_return = true;
};

} /* namespace mch */
