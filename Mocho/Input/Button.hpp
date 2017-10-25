/*
 * Button.hpp
 *
 *  Created on: Oct 24, 2017
 *      Author: santiago
 */

#pragma once

namespace mch {

class Button {
	public:
		void press(bool pressed);
		void update();

		void clear();

		bool isPressed()const;
		bool justUpdated()const;

	private:
		bool m_pressed;
		bool m_just_updated;

};

} /* namespace mch */
