/*
 * AppState.cpp
 *
 *  Created on: Sep 22, 2017
 *      Author: santiago
 */

#include "AppState.hpp"

namespace mch {

//empty default methods

AppState::~AppState() {}

bool AppState::update() {return true;}

bool AppState::draw(
		sf::RenderTarget& target,
		sf::RenderStates states) const {return true;}

bool AppState::input(
		const sf::Event& event) {return true;}

} /* namespace mch */
