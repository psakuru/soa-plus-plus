#ifndef EXTENSIBLEMAP_H
#define EXTENSIBLEMAP_H

#include <map>
#include <list>
#include <utility>
using namespace std;

template <typename Key, typename SchedulingInformation, typename Element>
class ExtensibleMap
{
protected:
    map<Key, pair<SchedulingInformation, list<Element> > > dataStructure;
public:
    virtual Element operator[](Key searchingKey) = 0; //Ridà un elemento nella lista contenuta alla riga specificata secono le politiche di scheduling
    virtual list<Element> getAllElementsIn(Key searchingKey)
    {
        return dataStructure[searchingKey].second;
    }
    virtual void insertElement(Key selectingKey, Element elementToInsert) = 0;
    virtual void clearElement(Key selectingKey, Element elementToClear) = 0;
    virtual void clearElementList(Key selectingKey)
    {
        dataStructure.erase(selectingKey);
    }
};

#endif // EXTENSIBLEMAP_H
