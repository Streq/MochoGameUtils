/*
 * AppStack.cpp
 *
 *  Created on: Sep 22, 2017
 *      Author: santiago
 */

#include "AppStack.hpp"
#include <utility>
#include <algorithm>

#include "Mocho/Application/AppState.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
namespace mch {


void AppStack::update() {
	std::find_if_not(stack.rbegin(),stack.rend(),
		[](StatePtr& state){
			return state->update();
		}
	);
}

void AppStack::draw(
		sf::RenderTarget& target,
		sf::RenderStates states) const {

	std::for_each(stack.crbegin(),stack.crend(),
		[&target, &states](const StatePtr& state){
			state->draw(target,states);
		}
	);
}

void AppStack::input(const sf::Event& event) {
	std::find_if_not(stack.rbegin(),stack.rend(),
		[&event](StatePtr& state){
			return state->input(event);
		}
	);
}

void AppStack::pushRequest(Action a, StatePtr ptr) {
}

void AppStack::applyChanges() {
}

void AppStack::pushState(StatePtr state) {
	if(state)
		stack.push_back(std::move(state));
}

void AppStack::clear() {
}

AppStack::StatePtr AppStack::popState() {
	StatePtr ret(stack.back().release());
	stack.pop_back();
	return ret;
}

void AppStack::setContext(AppContext& ctx){
	this->ctx=&ctx;
}


} /* namespace mch */
