#ifndef SINGLETONOBJECT_H
#define SINGLETONOBJECT_H

#include <boost/thread/mutex.hpp>
#include <boost/pool/detail/guard.hpp>

template <typename T>
class SingletonObject
{
private:
    static T* instance;
    static boost::mutex lifecycleControl;
    SingletonObject() {}
    ~SingletonObject() {}
public:
    static T* getInstance()
    {
        boost::details::pool::guard<boost::mutex> lifecycleGuard(lifecycleControl);
        if(instance == NULL) instance = new T();
        return instance;
    }
    static void destroyInstance()
    {
        boost::details::pool::guard<boost::mutex> lifecycleGuard(lifecycleControl);
        delete instance;
        instance = NULL;
    }
};

template <typename T> T* SingletonObject<T>::instance = NULL;
template <typename T> boost::mutex SingletonObject<T>::lifecycleControl;

#endif //SINGLETONOBJECT_H
