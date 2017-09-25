/*
 * Application.hpp
 *
 *  Created on: Sep 22, 2017
 *      Author: santiago
 */

#pragma once

#include "Mocho/definitions.hpp"
#include "Mocho/Application/AppContext.hpp"
#include "Mocho/Application/AppStack.hpp"

namespace mch {
class AppState;


class Application {
	public:
		//Just create the application man
		//like it won't run or be initialized or notn
		Application();

		//Initializes the Application with the given state on the stack.
		//init() is then called for all states in the stack.
		void init(std::unique_ptr<AppState> initState
				, AppSettings settings = AppSettings::Default);

		//MAIN LOOP, CALL THIS AFTER INIT TO START ROLLING KNOW ADDAM SAYN
		void run();

		//Update every state on the stack until one of them returns false
		void update();

		//Draw every state on the stack
		void draw();



	private:
		void input();

		AppContext ctx;
		AppStack stack;

		int64 micros_since_last_render;

};

} /* namespace mch */
