/*
 * ButtonCallback.hpp
 *
 *  Created on: Oct 24, 2017
 *      Author: santiago
 */

#pragma once
#include <Mocho/Input/Button.hpp>
#include <functional>
namespace mch {

class ButtonCallback : public Button{
	public:
		void update();

		void setOnPressed(std::function<void(void)> callback);
		void setOnReleased(std::function<void(void)> callback);
		void setHoldDown(std::function<void(void)> callback);


	private:
		std::function<void(void)> m_pressed_callback;
		std::function<void(void)> m_released_callback;
		std::function<void(void)> m_hold_down_callback;

};

} /* namespace mch */
