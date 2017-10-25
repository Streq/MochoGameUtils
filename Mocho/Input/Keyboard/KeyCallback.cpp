/*
 * Button.cpp
 *
 *  Created on: Oct 22, 2017
 *      Author: santiago
 */

#include "KeyCallback.hpp"

namespace mch {
namespace Keyboard {

void KeyCallback::handle(const sf::Event& e){
	auto code = e.key.code;
	auto type = e.type;
	if(code == m_code){
		switch (type){
			case sf::Event::EventType::KeyPressed:{
				press(true);
			}break;
			case sf::Event::EventType::KeyReleased:{
				press(false);
			}break;
		}
	}
};

unsigned KeyCallback::getKey()const {return (sf::Keyboard::Key)m_code;};

void KeyCallback::setKey(sf::Keyboard::Key key){m_code=(unsigned)key;};


}
}/* namespace mch */

