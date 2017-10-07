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


#include<iostream>
namespace mch {


void AppStack::update() {
	std::find_if_not(m_stack.rbegin(),m_stack.rend(),
		[](StatePtr& state){
			return state->update();
		}
	);
	applyChanges();
}

void AppStack::draw(
		sf::RenderTarget& target,
		sf::RenderStates states) const {

	std::for_each(m_stack.crbegin(),m_stack.crend(),
		[&target, &states](const StatePtr& state){
			state->draw(target,states);
		}
	);
}

void AppStack::input(const sf::Event& event) {
	std::find_if_not(m_stack.rbegin(),m_stack.rend(),
		[&event](StatePtr& state){
			return state->input(event);
		}
	);
}

void AppStack::pushRequest(Action action, StatePtr ptr) {
	m_requests.push_back(mch::AppStack::Request{action,std::move(ptr)});
	//std::cout<<m_requests.size()<<'\n';
}

void AppStack::applyChanges() {
	for(auto& req:m_requests){
		switch(req.action){
			case Action::clear:{
				clear();
			}break;
			case Action::pop:{
				popState();
			}break;
			case Action::push:{
				pushState(std::move(req.state));
			}break;
		}
	};
	m_requests.clear();
}

void AppStack::pushState(StatePtr state) {
	if(state){
		state->setStack(*this);
		state->setContext(*(this->m_ctx));
		m_stack.push_back(std::move(state));
	}
}

void AppStack::clear() {
	m_stack.clear();
}

AppStack::StatePtr AppStack::popState() {
	StatePtr ret(m_stack.back().release());
	m_stack.pop_back();
	return ret;
}


void AppStack::setContext(AppContext& ctx){
	this->m_ctx=&ctx;
}



bool AppStack::isEmpty() const {
	return m_stack.empty();
}

AppStack::AppStack(): m_ctx(nullptr),m_requests(0),m_stack(0){
}
} /* namespace mch */

