/*
 * AppStack.hpp
 *
 *  Created on: Sep 22, 2017
 *      Author: santiago
 */

#pragma once
#include <vector>
#include<memory>
namespace mch {
struct AppState;


class AppStack {
	public:
		using StatePtr = std::unique_ptr<AppState>;

		void update();
		void draw(sf::RenderTarget& target, sf::RenderStates states)const;
		void input(const sf::Event& event);


		enum class Action{
			push,
			pop,
			clear
		};

		void pushRequest(Action a, StatePtr ptr = nullptr);
		void applyChanges();

	private:
		void pushState(StatePtr state);
		void clear();
		StatePtr popState();

		std::vector<StatePtr> stack;

		struct Request{Action action; StatePtr state;};

		std::vector<Request> requests;

};

} /* namespace mch */
