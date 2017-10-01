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
		AppStack();

		void setContext(AppContext& m_ctx);


		void update();
		void draw(sf::RenderTarget& target, sf::RenderStates states)const;
		void input(const sf::Event& event);

		bool isEmpty()const;

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

		struct Request{Action action; StatePtr state;};
		std::vector<StatePtr> m_stack;
		std::vector<Request> m_requests;
		AppContext* m_ctx;
};

} /* namespace mch */
