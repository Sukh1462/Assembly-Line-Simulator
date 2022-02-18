// Name: Sukhmanpreet Kaur
// Seneca Student ID: 134893205
// Seneca email: skmalhi2@myseneca.ca
// Date of completion: 04th december 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <string>

namespace sdds {
	class Station {
		int m_id = 0;
		std::string m_name = "";
		std::string m_description = "";
		size_t m_serialNum = 0;
		size_t m_numCurrentItems = 0;

		static size_t m_widthField;
		static size_t id_generator;

	public:
		Station(const std::string& src);

		const std::string& getItemName() const;

		size_t getNextSerialNumber();

		size_t getQuantity() const;

		void updateQuantity();

		void display(std::ostream& os, bool full) const;

	};
}


#endif

