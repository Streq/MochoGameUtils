/*
 * AppState.cpp
 *
 *  Created on: Sep 22, 2017
 *      Author: santiago
 */

#include "AppState.hpp"
#include <utility>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <Mocho/Application/AppStack.hpp>


namespace mch {

//empty default methods

AppState::~AppState() {}

bool AppState::update() {return true;}

void AppState::draw(
		sf::RenderTarget& target,
		sf::RenderStates states) const {}

bool AppState::input(const sf::Event& event) {return true;}


void AppState::requestPop() {
	stack->pushRequest(AppStack::Action::pop);
}

void AppState::requestPush(
		ptr state) {
	stack->pushRequest(AppStack::Action::push, std::move(state));
}

void AppState::requestClear() {
	stack->pushRequest(AppStack::Action::clear);
}

void AppState::setStack(AppStack& stack) {
	this->stack=&stack;
}

AppContext& AppState::getContext() {
	return *ctx;
}

const AppContext& AppState::getContext() const{
	return *ctx;
}


void mch::AppState::setContext(AppContext& ctx) {
	this->ctx=&ctx;
}

} /* namespace mch */
