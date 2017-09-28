/*
 * SpriteBatch.cpp
 *
 *  Created on: Sep 25, 2017
 *      Author: santiago
 */

#include "SpriteBatch.hpp"

#include<SFML/System/Vector2.hpp>

#include<SFML/Graphics/RenderTarget.hpp>
#include<SFML/Graphics/Sprite.hpp>
#include<SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/Transform.hpp>
#include<SFML/Graphics/PrimitiveType.hpp>
namespace mch {


SpriteBatch::SpriteBatch
		( const sf::Texture& texture
		, int reserve
		)
		: array(sf::PrimitiveType::TrianglesStrip,reserve*6-2)
		, texture(&texture)
{
}

void SpriteBatch::setTexture(sf::Texture& texture) {
	this->texture=&texture;
}

void SpriteBatch::addSprite(const sf::Sprite& sprite) {
	addSprite
		( sprite.getTextureRect()
		, sprite.getTransform()
		, sprite.getColor());

}

SpriteBatch::SpriteBatch()
	: array(sf::PrimitiveType::TrianglesStrip)
	, texture(nullptr)
{}

void SpriteBatch::addSprite(
		const sf::IntRect& texRect,
		const sf::Transform& transform,
		const sf::Color& color) {

	auto vcount = array.getVertexCount();
	array.resize(vcount + 6);
	sf::Vertex* init = &array[vcount];

	for(int i = 0; i<6; ++i){
		(init+i)->color=color;
	}

	sf::Vector2f pos(0.f,0.f);

	(init+0)->position = transform*pos;
	(init+0)->texCoords = sf::Vector2f(texRect.left,texRect.top)+pos;
	*(init+1)=*(init+0);

	pos.x = texRect.width;

	(init+2)->position = transform*pos;
	(init+2)->texCoords = sf::Vector2f(texRect.left,texRect.top)+pos;

	pos.x = 0;
	pos.y = texRect.height;

	(init+3)->position = transform*pos;
	(init+3)->texCoords = sf::Vector2f(texRect.left,texRect.top)+pos;

	pos.x = texRect.width;

	(init+4)->position = transform*pos;
	(init+4)->texCoords = sf::Vector2f(texRect.left,texRect.top)+pos;
	*(init+5)=*(init+4);
}

void SpriteBatch::draw(
		sf::RenderTarget& target,
		sf::RenderStates states) const {
	states.texture = texture;
	target.draw(array,states);
}
} /* namespace mch */
