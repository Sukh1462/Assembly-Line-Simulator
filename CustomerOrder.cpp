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
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"


namespace sdds {
    size_t CustomerOrder::m_widthField = 0u;

    CustomerOrder::CustomerOrder(const std::string& str)
    {
        Utilities u;
        bool more = true;
        size_t position = 0u;
        size_t index = 0u;

            m_name = u.extractToken(str, position, more);
            m_product = u.extractToken(str, position, more);
            m_cntItem = std::count(str.begin(), str.end(), u.getDelimiter()) - 1;

            if (m_cntItem) {
                m_lstItem = new Item * [m_cntItem];

            }
                

            while (more && m_cntItem) {
                m_lstItem[index] = new Item(u.extractToken(str, position, more));
                index++;
            }

            CustomerOrder::m_widthField = std::max(u.getFieldWidth(), CustomerOrder::m_widthField);


     
    }

    CustomerOrder::CustomerOrder(const CustomerOrder& src) {
        throw false;
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
        *this = std::move(src);
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
        if (this != &src) {
            if (m_lstItem) {
                for (auto i = 0u; i < m_cntItem; ++i)
                    delete m_lstItem[i];

                delete[] m_lstItem;
            }

            m_name = src.m_name;
            m_product = src.m_product;
            m_cntItem = src.m_cntItem;
            m_lstItem = src.m_lstItem;

            src.m_name = "";
            src.m_product = "";
            src.m_cntItem = 0u;
            src.m_lstItem = nullptr;
        }

        return *this;
    }

    CustomerOrder::~CustomerOrder() {
         
            for (size_t i = 0u; i < m_cntItem; ++i)
                delete m_lstItem[i];

            delete[] m_lstItem;
           
        
    }

    bool CustomerOrder::isFilled() const {
    

       bool returner = true;

        for (auto i = 0u; returner == true && i < m_cntItem; i++) {
            if (!m_lstItem[i]->m_isFilled) returner = false;
        }

        return returner;
   
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
       
        bool returner = true;

        for (auto i = 0u; i < m_cntItem; i++) {
           
                if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) returner = false;

            
          
           
        }

        return returner;

    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        for (size_t i = 0u; i < m_cntItem; i++) {
            if (m_lstItem[i]->m_itemName == station.getItemName()) {
               if (station.getQuantity()) {
                    station.updateQuantity();
                    m_lstItem[i]->m_isFilled = true;

                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    os << "    Filled ";
                }
               else {
                   os << "    Unable to fill ";

               }
                    

                os << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
            }
        }
    }

    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << m_product << std::endl;

        for (size_t i = 0u; i < m_cntItem; i++) {
            os << "[" << std::right << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";

            os << std::left << std::setw(CustomerOrder::m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName;

            os << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
        }
    }
}

    





