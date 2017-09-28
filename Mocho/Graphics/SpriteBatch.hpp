/*
 * SpriteBatch.hpp
 *
 *  Created on: Sep 25, 2017
 *      Author: santiago
 */

#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
namespace sf{
	class Sprite;
	class Texture;
}
namespace mch {

class SpriteBatch : public sf::Drawable {
	public:
		SpriteBatch();
		SpriteBatch(const sf::Texture& texture, int reserve = 1);

		void setTexture(sf::Texture& texture);
		void addSprite(const sf::Sprite& sprite);
		void addSprite
				( const sf::IntRect& texRect = sf::IntRect(0,0,0,0)
				, const sf::Transform& transform = sf::Transform::Identity
				, const sf::Color& color = sf::Color::White);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	private:
		sf::VertexArray array;
		const sf::Texture* texture;

};

} /* namespace mch */
