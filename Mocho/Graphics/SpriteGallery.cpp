#include "SpriteGallery.hpp"
#include "Mocho/math.hpp"
namespace mch{

void SpriteGallery::addFrame(sf::Sprite&& frame){
	m_sprites.push_back(std::move(frame));
}

int SpriteGallery::fixIndex(int index)const{
	int frames = m_sprites.size();
	if(frames<=1)return 0;

	switch(m_type){
		case Type::Once:{
			index = clamp(index,0,frames-1);
		}break;
		case Type::Loop:{
			index = modulo(index,frames);
		}break;
		case Type::BackAndForth:{
			auto frames2 = frames*2 - 2;
			index = modulo(index,frames2);
			index = index > frames-1
				? frames2 - index
				: index;
		}break;
	}

	return index;
}

const sf::Sprite& SpriteGallery::getFrame(int index)const{
	assert(!m_sprites.empty());
	return m_sprites[fixIndex(index)];
}

void SpriteGallery::setAnimationType(Type type){m_type=type;}

void SpriteGallery::setSprites(std::vector<sf::Sprite>&& sprites){
	m_sprites=std::move(sprites);
}


}
