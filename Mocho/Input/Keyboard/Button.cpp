/*
 * Button.cpp
 *
 *  Created on: Oct 22, 2017
 *      Author: santiago
 */

#include <Mocho/Input/Keyboard/Button.hpp>

namespace mch {
namespace Keyboard {
		void Button::handle(const sf::Event& e){
			auto code = e.key.code;
			auto type = e.type;
			if(code == m_code){
				switch (type){
					case sf::Event::EventType::KeyPressed:{
						update(true);
					}break;
					case sf::Event::EventType::KeyReleased:{
						update(false);
					}break;
				}
			}
		};
		bool Button::isPressed()const {return m_pressed;};
		bool Button::isJustUpdated()const {return m_just_updated;};
		unsigned Button::getButton()const {return (sf::Keyboard::Key)m_code;};
		void Button::setKey(sf::Keyboard::Key key){m_code=(unsigned)key;};

		void Button::update(bool pressed){
			m_just_updated = (pressed!=m_pressed);
			m_pressed = pressed;
		}

		void Button::clear(){
			m_just_updated = false;
			m_pressed = false;
		}
}
}/* namespace mch */
