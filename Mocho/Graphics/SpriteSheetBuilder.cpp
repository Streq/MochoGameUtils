/*
 * SpriteSheetReader.cpp
 *
 *  Created on: Oct 11, 2017
 *      Author: santiago
 */

#include "SpriteSheetBuilder.hpp"
#include "Mocho/math.hpp"
#include <assert.h>
namespace mch {


std::vector<sf::Sprite>
SpriteSheetBuilder::makeSheet
	( const sf::Texture& 	texture)
{
	assert(m_frame_size.x!=0 && m_frame_size.y!=0);

	auto texSize = texture.getSize();
	auto h_frames = texSize.x/m_frame_size.x;
	auto v_frames = texSize.y/m_frame_size.y;

	if(!m_frames){
		m_frames = (h_frames)*(v_frames);
	}

	assert(m_frames>=0);

	std::vector<sf::Sprite> ret(m_frames);
	sf::IntRect rect;
	rect.width = m_frame_size.x;
	rect.height = m_frame_size.y;
	int i = m_index.x;
	int j = m_index.y;
	for(auto& sprite : ret){
		sprite.setTexture(texture);

		rect.left=i*m_frame_size.x;
		rect.top=j*m_frame_size.y;

		sprite.setTextureRect(rect);

		if(m_horizontal_read){
			i+=m_positive_read - !m_positive_read;
			if(i<0||i>=h_frames){
				j+=m_positive_return - !m_positive_return;
			}
		}else{
			j+=m_positive_read - !m_positive_read;
			if(j<0||j>=v_frames){
				i+=m_positive_return - !m_positive_return;
			}
		}
		i=modulo(i,h_frames);
		j=modulo(j,v_frames);



	}


	return ret;
}

void SpriteSheetBuilder::setFrames(
		unsigned frames) {
	m_frames=frames;
}

void SpriteSheetBuilder::setSize(
		const sf::Vector2u& size) {
	m_frame_size=size;
}

void SpriteSheetBuilder::setHorizontalRead(
		bool horizontal) {
	m_horizontal_read=horizontal;
}

void SpriteSheetBuilder::setIndex(
		sf::Vector2i index) {
	m_index=index;
}

void SpriteSheetBuilder::setReadForward(
		bool forward) {
	m_positive_read=forward;
}

void SpriteSheetBuilder::setReturnForward(
		bool forward) {
	m_positive_return=forward;
}
} /* namespace mch */
