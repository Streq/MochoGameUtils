/*
 * AppState.hpp
 *
 *  Created on: Sep 22, 2017
 *      Author: santiago
 */

#pragma once
#include <memory>
namespace sf{
struct Event;
struct RenderTarget;
struct RenderStates;
}

namespace mch {
class AppStack;
struct AppSettings;
struct AppContext;

class AppState {
	public:
		using ptr = std::unique_ptr<AppState>;

		virtual ~AppState();


		//Update the state
		//@returns bool stating wether or not to keep updating
		// for next states in the stack
		virtual bool update();

		//Draw the current state
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

		//Handle a given event
		//@returns bool stating wether or not to keep handling input
		// for next states in the stack
		virtual bool input(const sf::Event& event);

	protected:
		//Stack operations, they take effect at the end of every main loop
		void requestPop();
		void requestPush(ptr state);
		void requestClear();

		//Use this to access the context of the application
		AppContext& getContext();
		const AppContext& getContext()const;

	private:

		AppContext* ctx;
		AppStack* stack;

		friend class AppStack;
		void setContext(AppContext& ctx);
		void setStack(AppStack& stack);
};

} /* namespace mch */
