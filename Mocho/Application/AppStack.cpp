/*
 * AppStack.cpp
 *
 *  Created on: Sep 22, 2017
 *      Author: santiago
 */

#include "AppStack.hpp"

namespace mch {


void AppStack::update() {
	for(auto& state:stack){
		if(!state->update())break;
	}
}

void AppStack::draw(
		sf::RenderTarget& target,
		sf::RenderStates states) const {
	for(auto& state:stack){
		if(!state->draw(target,states))break;
	}
}

void AppStack::input(
		const sf::Event& event) {
	for(auto& state:stack){
		if(!state->input(event))break;
	}
}

void AppStack::pushRequest(
		Action a, StatePtr ptr) {
}

void AppStack::applyChanges() {
}

void AppStack::pushState(
		StatePtr state) {
}

void AppStack::clear() {
}

AppStack::StatePtr AppStack::popState() {
}

} /* namespace mch */
