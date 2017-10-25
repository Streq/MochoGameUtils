/*
 * State.hpp
 *
 *  Created on: Oct 24, 2017
 *      Author: santiago
 */

#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <Mocho/Input/Button.hpp>
#include <SFML/Window/Event.hpp>
namespace mch {
namespace Keyboard {

class State {
	public:

		void handle(const sf::Event& e){
			switch(e.type){
				case sf::Event::KeyPressed:{
					m_keyset[e.key.code].press(true);
				}break;
				case sf::Event::KeyReleased:{
					m_keyset[e.key.code].press(false);
				}break;
				case sf::Event::LostFocus:{

				}break;
			}
		};

		void update(){
			for(auto& key : m_keyset){
				key.update();
			}
		}
		void clear(){
			for(auto& key : m_keyset){
				key.press(false);
			}
		}

		bool checkPressed(sf::Keyboard::Key key)const{return m_keyset[key].isPressed();};
		bool checkJustUpdated(sf::Keyboard::Key key)const{return m_keyset[key].justUpdated();};

	private:
		Button m_keyset[sf::Keyboard::Key::KeyCount];

};

} /* namespace Keyboard */
} /* namespace mch */
