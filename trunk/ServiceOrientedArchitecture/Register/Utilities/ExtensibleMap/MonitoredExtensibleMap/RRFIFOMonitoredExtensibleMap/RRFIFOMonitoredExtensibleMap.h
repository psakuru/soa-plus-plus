#ifndef RRFIFOMONITOREDEXTENSIBLEMAP_H
#define RRFIFOMONITOREDEXTENSIBLEMAP_H

#include "../MonitoredExtensibleMap.h"
#include <iostream>
using namespace std;

template <typename Key, typename Element>
class RRFIFOMonitoredExtensibleMap
    : public MonitoredExtensibleMap<Key, int, Element>
{
protected:
    Element selectionOperatorImplementation(Key searchingKey)
    {
        if(this->dataStructure.find(searchingKey) == this->dataStructure.end())
        {
            return Element(); //valore vuoto! verrà ritornato al client che dovrà interpretarlo come "servizio non disponibile"
        }
        if(this->dataStructure[searchingKey].second.size() == 0)
        {
            return Element(); //valore vuoto! verrà ritornato al client che dovrà interpretarlo come "servizio non disponibile"
        }
        typename list<Element>::iterator i = this->dataStructure[searchingKey].second.begin();
        for(int j = 0; j < this->dataStructure[searchingKey].first; j++)
        {
            i++;
        }
        this->dataStructure[searchingKey].first = (this->dataStructure[searchingKey].first+1)%this->dataStructure[searchingKey].second.size();
        return *i;
    }
    void insertElementImplementation(Key searchingKey, Element elementToInsert)
    {
        if(this->dataStructure[searchingKey].second.empty()) this->dataStructure[searchingKey].first = 0;
        this->dataStructure[searchingKey].second.push_back(elementToInsert);
    }
    void clearElementImplementation(Key selectingKey, Element elementToClear)
    {
        if(this->dataStructure.find(selectingKey) == this->dataStructure.end()) return;
        if(this->dataStructure[selectingKey].second.size() == 0) return;
        typename list<Element>::iterator i = this->dataStructure[selectingKey].second.begin();
        while((i != (this->dataStructure[selectingKey].second.end())) && ((*i).compare(elementToClear) != 0))
        {
            i++;
        }
        if(i != this->dataStructure[selectingKey].second.end())
        {
            this->dataStructure[selectingKey].second.erase(i);
            (this->dataStructure[selectingKey].first == ((int)(this->dataStructure[selectingKey].second.size())+1))?
            this->dataStructure[selectingKey].first-- : this->dataStructure[selectingKey].first;
        }
        else return;
    }
};

#endif // RRFIFOMONITOREDEXTENSIBLEMAP_H
