#ifndef REGISTERMANAGER_H
#define REGISTERMANAGER_H

#include "../../ObjectInterfaces/SingletonObject/SingletonObject.h"
#include "Utilities/ExtensibleMap/MonitoredExtensibleMap/RRFIFOMonitoredExtensibleMap/RRFIFOMonitoredExtensibleMap.h"
#include "../Service/Skeleton/RegistrablePoolableCyclicCallableSkeleton/RegistrablePoolableCyclicCallableSkeleton.h"
#include "../Service/Skeleton/Exceptions/DOSAttackInProgress.h"
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
        if(requestedOperation.compare("search") == 0) searchInMap();
        //Se nessuno di questi if si attiva il registro non fa niente, alla fine risponde lista vuota e tutti contenti
        inputParameters.clear();
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
            sharedRegister->print();
            i++;
        }
        //inputParameters.clear();
    }
    virtual void searchInMap()
    {
        cout << "Ricevuta richiesta di ricerca sulla Map: " << endl;
        RegisterMap<string, string>* sharedRegister = SingletonObject< RegisterMap<string, string> >::getInstance(); //deve essere singleton!
        SerializableObjectList::iterator i = inputParameters.begin();
        string key = *((string*)(*i)->getValue());
        cout << "chiave di ricerca:: " << key << endl;
        string* searchResult = new string((*sharedRegister)[key]);
        outputParameters.push_back(new String(searchResult, false));
        //inputParameters.clear();
    }
public:
    RegisterManager() : Skeleton("register"), RegistrablePoolableCyclicCallableSkeleton("register") {}
    virtual void receiveParameters() //throws SocketException, IncompatibleTypes
    {
        SerializableObjectList::size_type* incomingParametersSizePointer =
            ((SerializableObjectList::size_type*)socket->receiveMessage(sizeof(SerializableObjectList::size_type)));
        SerializableObjectList::size_type incomingParametersSize = *incomingParametersSizePointer;
        free(incomingParametersSizePointer);
        if((int)incomingParametersSize > 1024 || (int)incomingParametersSize <= 0)
        {
            cout << "DOS ATTACK!" << endl;
            throw DOSAttackInProgress();
        }
        SerializableObjectList* incomingParameters = new SerializableObjectList;
        for(unsigned int i = 0; i < (incomingParametersSize); i++)
        {
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
    ~RegisterManager()
    {
        //Elimina l' istanza Singleton
        SingletonObject< RegisterMap<string, string> >::destroyInstance();
    }
};

#endif // REGISTERMANAGER_H
