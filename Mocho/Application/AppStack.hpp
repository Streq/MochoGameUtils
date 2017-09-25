/*
 * AppStack.hpp
 *
 *  Created on: Sep 22, 2017
 *      Author: santiago
 */

#pragma once
#include <vector>
#include <memory>
namespace sf{
class RenderTarget;
class RenderStates;
class Event;
}

namespace mch {
struct AppState;
class AppContext;

class AppStack {
	public:
		using StatePtr = std::unique_ptr<AppState>;
		void setContext(AppContext& ctx);


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


		void pushState(StatePtr state);
		void clear();
		StatePtr popState();


	private:

		std::vector<StatePtr> stack;

		struct Request{Action action; StatePtr state;};

		std::vector<Request> requests;

		AppContext* ctx;
};

} /* namespace mch */
