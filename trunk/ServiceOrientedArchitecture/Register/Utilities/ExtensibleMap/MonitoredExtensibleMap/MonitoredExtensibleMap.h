#ifndef MONITOREDEXTENSIBLEMAP_H
#define MONITOREDEXTENSIBLEMAP_H

#include "../ExtensibleMap.h"
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>

template <typename Key, typename SchedulingInformation, typename Element>
class MonitoredExtensibleMap
    : public ExtensibleMap<Key, SchedulingInformation, Element>
{
private:
    boost::shared_mutex mutex;
protected:
    virtual Element selectionOperatorImplementation(Key searchingKey) = 0;
    virtual void insertElementImplementation(Key selectingKey, Element elementToInsert) = 0;
    virtual void clearElementImplementation(Key selectingKey, Element elementToClear) = 0;
public:
    virtual Element operator[](Key searchingKey)
    {
        boost::shared_lock<boost::shared_mutex> readersLock(mutex);
        return this->selectionOperatorImplementation(searchingKey);
    }
    virtual list<Element> getAllElementsIn(Key searchingKey)
    {
        boost::shared_lock<boost::shared_mutex> readersLock(mutex);
        return this->dataStructure[searchingKey].second;
    }
    virtual void insertElement(Key selectingKey, Element elementToInsert)
    {
        boost::unique_lock<boost::shared_mutex> writersLock(mutex);
        this->insertElementImplementation(selectingKey, elementToInsert);
    }
    virtual void clearElement(Key selectingKey, Element elementToClear)
    {
        boost::unique_lock<boost::shared_mutex> writersLock(mutex);
        this->clearElementImplementation(selectingKey, elementToClear);
    }
    virtual void clearElementList(Key selectingKey)
    {
        boost::unique_lock<boost::shared_mutex> writersLock(mutex);
        this->dataStructure.erase(selectingKey);
    }
    void print()
    {
        typename map<Key, pair<SchedulingInformation, list<Element> > >::iterator i = this->dataStructure.begin();
        for(; i != this->dataStructure.end(); i++)
        {
            cout << "[" << (*i).first << "]::";
            typename list<Element>::iterator j = (((*i).second).second).begin();
            for(; j != (((*i).second).second).end(); j++)
            {
                cout << "--->" << (*j);
            }
            cout << endl;
        }
    }
};

#endif // MONITOREDEXTENSIBLEMAP_H
