// Name: Sukhmanpreet Kaur
// Seneca Student ID: 134893205
// Seneca email: skmalhi2@myseneca.ca
// Date of completion: 04th december 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <string>
#include "Workstation.h"

using namespace std;

namespace sdds
{
    std::deque<CustomerOrder> pending;
    std::deque<CustomerOrder> completed;
    std::deque<CustomerOrder> incomplete;

    Workstation::Workstation(const std::string& str) : Station(str) {};
    

    void Workstation::fill(std::ostream& os) {
        if (!m_orders.empty())

            m_orders.front().fillItem(*this, os);
    }

    bool Workstation::attemptToMoveOrder() {

        bool moved = false;

        if (!m_orders.empty()) {

            if (m_orders.front().isItemFilled(getItemName())) {

                if (m_pNextStation)
                    *m_pNextStation += std::move(m_orders.front());

                else if (!m_orders.front().isFilled())
                    incomplete.push_back(std::move(m_orders.front()));

                else
                    completed.push_back(std::move(m_orders.front()));

                moved = true;
                m_orders.pop_front();
            }
            else if (getQuantity() < 1) {
                if (!m_pNextStation) {
                    incomplete.push_back(std::move(m_orders.front()));
                }
                else {
                    *m_pNextStation += std::move(m_orders.front());
                }

                moved = true;
                m_orders.pop_front();
            }
        }

        return moved;
    }

    void Workstation::setNextStation(Workstation* station) {
        m_pNextStation = station;
    }

    Workstation* Workstation::getNextStation() const {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream& os) const {

        os << getItemName() << " --> ";

        if (!m_pNextStation) {
            os << "End of Line" << endl;
        }

        else os << m_pNextStation->getItemName() << endl;


    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {

        m_orders.push_back(move(newOrder));
        return *this;
    }
}
