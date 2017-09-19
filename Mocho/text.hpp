#pragma once
#include <SFML/Graphics/Text.hpp>

#include <utility>
#include <cmath>


namespace mch{
using Text = sf::Text;

namespace text{
/**
Takes a text and sets its origin to its floored local center
*/
inline void centerOrigin(Text& t) {
	auto bounds = t.getLocalBounds();
	t.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}





/**
Takes a string and returns a wrapped copy which has the specified line width

@param str the string to wrap
@param lineWidth the desired line width
@return a wrapped copy of str
*/
inline std::string wrap(const std::string& str, const size_t lineWidth) {
	std::string result{ str };
	const auto strlen = result.length(); 
	//Begin parse
	//i: Current position on the string
	//lineDist: Current position from last line break ('\n')
	//lastSpace: Position of the last space (' ') found in the current line
	for (size_t i = 0, lineDist = 0, lastSpace = strlen;
			i < strlen; i++, lineDist++) {
		switch (result[i]) {
			case '\n':{
				//if it's a new line we reset lineDist and clear
				//lastSpace since it's no longer useful
				lineDist = 0;
				lastSpace = strlen;
			}break;
			case ' ': {//if it's a space we save its position
				lastSpace = i;
			}break;
		}
		//if we are at or past the line limit and we have previously found a space
		// we replace said space with a line break
		if (lineDist >= lineWidth && lastSpace != strlen) {
			result[lastSpace] = '\n';
			lineDist = i - lastSpace; //recalculate lineDist
			lastSpace = strlen;//clear lastSpace
		}
	}
	return result;
	
}



}
}
