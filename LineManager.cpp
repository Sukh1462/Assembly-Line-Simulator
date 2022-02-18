// Name: Sukhmanpreet Kaur
// Seneca Student ID: 134893205
// Seneca email: skmalhi2@myseneca.ca
// Date of completion: 04th december 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <set>
#include "LineManager.h"
#include "Utilities.h"

using namespace std;

namespace sdds
{
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        std::ifstream f(file);

        if (!f) {
            throw std::string("Not able to open file!\n");
        }

        Utilities utils;
        std::string str;

        while (getline(f, str)) {
            size_t pos = 0;
            bool more = true;
            std::string token, nextToken;
            Workstation* firstWs;
            Workstation* nextWs;

            token = utils.extractToken(str, pos, more);
            firstWs = *std::find_if(stations.begin(), stations.end(), [&token](const Workstation* ws) {
                return ws->getItemName() == token;
                });


            if (more) {
                nextToken = utils.extractToken(str, pos, more);

                nextWs = *std::find_if(stations.begin(), stations.end(), [&nextToken](const Workstation* ws) {
                    return ws->getItemName() == nextToken;
                    });

                if (nextWs) {
                    firstWs->setNextStation(nextWs);
                }
            }


            activeLine.push_back(firstWs);
            m_firstStation = activeLine.front();
            m_cntCustomerOrder = pending.size();
        }
    }

    void LineManager::linkStations() {
        Workstation* next_Wstation = m_firstStation;
        vector<Workstation*>  v_Wstation;

        while (next_Wstation) {
            v_Wstation.push_back(next_Wstation);
            next_Wstation = next_Wstation->getNextStation();
        }

        activeLine = v_Wstation;
    }

    bool LineManager::run(std::ostream& os) {
  
        static size_t counter = 0;

        os << "Line Manager Iteration: " << ++counter << "\n";

        if (!pending.empty()) {
            *m_firstStation += std::move(pending.front());
            pending.pop_front();
        }


        std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* w) {
            w->fill(os);
            });


        std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* w) {
            w->attemptToMoveOrder();
            });

        return m_cntCustomerOrder == (completed.size() + incomplete.size());
    }

    void LineManager::display(std::ostream& os) const {
        std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* w) {
            w->display(os);
            });
    }
}