// Name: Sukhmanpreet Kaur
// Seneca Student ID: 134893205
// Seneca email: skmalhi2@myseneca.ca
// Date of completion: 04th december 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Utilities.h"
#include "Station.h"
namespace sdds {

	size_t Station::m_widthField = 0u;
	size_t Station::id_generator = 0u;

	Station::Station(const std::string& src)
	{
		Utilities localUtils;

		bool more = true;
		size_t position = 0u;
		m_id = ++Station::id_generator;

		m_name = localUtils.extractToken(src, position, more);
		m_serialNum = std::stoi(localUtils.extractToken(src, position, more));
		m_numCurrentItems = std::stoi(localUtils.extractToken(src, position, more));
		Station::m_widthField = std::max(localUtils.getFieldWidth(), Station::m_widthField);
		m_description = localUtils.extractToken(src, position, more);

	}


	const std::string& Station::getItemName() const {
		return m_name;
	}

	size_t Station::getNextSerialNumber() {
		m_serialNum++;
		return m_serialNum - 1;
	}

	size_t Station::getQuantity() const {
		return m_numCurrentItems;
	}

	void Station::updateQuantity() {
		m_numCurrentItems == 0 ? m_numCurrentItems = 0 : --m_numCurrentItems;
	}

	void Station::display(std::ostream& os, bool full) const {
		os << "[" << std::right << std::setw(3) << std::setfill('0') << m_id << "]";
		os << " Item: " << std::left << std::setw(Station::m_widthField) << std::setfill(' ') << m_name;
		os << " [" << std::right << std::setw(6) << std::setfill('0') << m_serialNum << "]";

		if (full) {
			os << " Quantity: " << std::left << std::setw(Station::m_widthField) << std::setfill(' ') << m_numCurrentItems;
			os << " Description: " << m_description << std::endl;
		}
		else
			os << std::endl;
	}
	
}