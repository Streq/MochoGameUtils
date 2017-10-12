#pragma once
#include<vector>

#include<SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/Sprite.hpp>

#include<assert.h>
namespace mch{
// This could be made a lot more lightweight
// if instead of sprites we just used their inner vertex arrays
// but that would make multitexture animations harder to implement
class SpriteGallery{
	public:
		enum class Type{
			Once,
			Loop,
			BackAndForth
		};

	public:
		
		const sf::Sprite& getFrame(int index)const;
		
		void addFrame(sf::Sprite&& frame);
		void setSprites(std::vector<sf::Sprite>&& sprites);
		void setAnimationType(Type type);
		
	private:
		int fixIndex(int index)const;
	private:
		std::vector<sf::Sprite> m_sprites;
		Type m_type;
		
};




}
