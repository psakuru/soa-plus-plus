#ifndef REGISTERMANAGER_H
#define REGISTERMANAGER_H

#include "../../ObjectInterfaces/SingletonObject/SingletonObject.h"
#include "Utilities/ExtensibleMap/MonitoredExtensibleMap/RRFIFOMonitoredExtensibleMap/RRFIFOMonitoredExtensibleMap.h"
#include "../Service/Skeleton/RegistrablePoolableCyclicCallableSkeleton/RegistrablePoolableCyclicCallableSkeleton.h"
#include "../../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
#include <string>
using namespace std;

template <template<typename, typename> class RegisterMap> /*devi passarmi una mappa template con 2 parametri Key e Elem, ci penso io a declinarli a string*/
class RegisterManager : public RegistrablePoolableCyclicCallableSkeleton
{
protected:
    void doService()
    {
        string requestedOperation(*((string*)(inputParameters.front())->getValue()));
        inputParameters.pop_front();
        if(requestedOperation.compare("publish") == 0) editMap("publish");
        if(requestedOperation.compare("censor") == 0) editMap("censor");
        //TODO droppare la richiesta o rispondere in qualche modo?
    }
    virtual void editMap(string command)
    {
        RegisterMap<string, string>* sharedRegister = SingletonObject< RegisterMap<string, string> >::getInstance(); //deve essere singleton!
        SerializableObjectList::iterator i = inputParameters.begin();
        while(i != inputParameters.end())
        {
            string entry = *((string*)(*i)->getValue());
            string key = entry.substr(0, entry.find_first_of('@'));
            string element = entry.substr(entry.find_first_of('@')+1);
            if(command.compare("publish") == 0)
            {
                sharedRegister->insertElement(key, element);
            }
            if(command.compare("censor") == 0)
            {
            sharedRegister->clearElement(key, element);
            }
            //TODO drop?
            sharedRegister->print();
            i++;
        }
        inputParameters.clear();
    }
public:
    RegisterManager() : Skeleton("register"), RegistrablePoolableCyclicCallableSkeleton("register") {}
    virtual void receiveParameters()
    {
        SerializableObjectList* incomingParameters = new SerializableObjectList;
        SerializableObjectList::size_type* incomingParametersSizePointer =
            ((SerializableObjectList::size_type*)socket->receiveMessage(sizeof(SerializableObjectList::size_type)));
        SerializableObjectList::size_type incomingParametersSize = *incomingParametersSizePointer;
        free(incomingParametersSizePointer);
        inputParameters.push_back(new String); //per l' operazione
        for(unsigned int i = 0; i < (incomingParametersSize-1); i++)
        {
            //TODO controllo sul tipo ritornato dal server!
            inputParameters.push_back(new String);
        }
        for(unsigned int i = 0; i < incomingParametersSize; i++)
        {
            incomingParameters->push_back(receiveParameter());
        }
        SerializableObjectList::iterator i = inputParameters.begin();
        SerializableObjectList::iterator j = incomingParameters->begin();
        while(i != inputParameters.end())
        {
            *(*i) = *(*j);
            i++;
            j++;
        }
        delete incomingParameters;
    }
};

#endif // REGISTERMANAGER_H
