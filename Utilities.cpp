// Name: Sukhmanpreet Kaur
// Seneca Student ID: 134893205
// Seneca email: skmalhi2@myseneca.ca
// Date of completion: 04th december 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <string>
#include <algorithm>
#include "Utilities.h"



namespace sdds{

	char Utilities::m_delimiter = ' ';
	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}
	std::string Utilities::extractToken(const std::string str, size_t& next_pos, bool& more)
	{
		std::string returner = "";
		size_t posn = next_pos;
		more = false;


		next_pos = str.find(m_delimiter, posn);

		if (next_pos == std::string::npos) {
			returner = str.substr(posn);
			m_widthField = std::max(returner.length(), m_widthField);
			
		}
		else if (next_pos == posn) {
	
			throw "   ERROR: No token.\n";
		}

		else {

			returner = str.substr(posn, (next_pos - posn));

			m_widthField = std::max(returner.length(), m_widthField);
			more = true;
		}

		next_pos++;
		return returner;
	}
	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}
