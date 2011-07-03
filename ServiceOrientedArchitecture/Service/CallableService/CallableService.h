#ifndef CALLABLE_SERVICE_H
#define CALLABLE_SERVICE_H

#include "../../../ObjectInterfaces/CallableObject/CallableObject.h"
#include "../Service.h"
#include <boost/thread/thread.hpp>
#include <iostream>
using namespace std;

/* Derivazione virtuale multipla da parametro template */
template <typename T>
class CallableService : public CallableObject, virtual public T
{
public:
    CallableService()
    {
        /*T instanceToTest;
        Service* polimorphicTest = dynamic_cast<Service*>(&instanceToTest);*/
        /* I costruttori di default della classe Service e delle sue derivate
           non fanno nulla, quindi se T è un tipo legale la sua istanziazione
           non comporta aperture di socket o altro...
           Il test del dynamic_cast, in caso T non sia un tipo legale,
           (non derivato da Service), fallisce a tempo di compilazione.
           */
    }
    CallableService(string serviceIdToSet) : T(serviceIdToSet)
    {
        cout << "TID:" << boost::this_thread::get_id() << " CallableService<" << (typeid(T)).name() << ">(" << serviceIdToSet << ")" << endl << endl;
        /*T instanceToTest;
        Service* polimorphicTest = dynamic_cast<Service*>(&instanceToTest);*/
    }
    CallableService(string serviceIdToSet, string ServiceRegistryToSet) : T(serviceIdToSet, ServiceRegistryToSet)
    {
        cout << "TID:" << boost::this_thread::get_id() << " CallableService<" << (typeid(T)).name() << ">(" << serviceIdToSet << ")" << endl << endl;
    }
    virtual ~CallableService() {}
    virtual void operator()() = 0;
};

#endif // CALLABLE_SERVICE_H
