/**
 * @file RegisterManager.h
 * @author  Sacco Cosimo <cosimosacco@gmail.com>, Silvestri Davide <davidesil.web@gmail.com>
 *
 * @section LICENSE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef REGISTERMANAGER_H
#define REGISTERMANAGER_H

#include "../../ObjectInterfaces/SingletonObject/SingletonObject.h"
#include "Utilities/ExtensibleMap/MonitoredExtensibleMap/RRFIFOMonitoredExtensibleMap/RRFIFOMonitoredExtensibleMap.h"
#include "../Service/Skeleton/RegistrablePoolableCyclicCallableSkeleton/RegistrablePoolableCyclicCallableSkeleton.h"
#include "../Service/Skeleton/Exceptions/DOSAttackInProgress.h"
#include "../../SerializableObjects/SerializationStrategies/StringSerializationStrategy/StringSerializationStrategy.h"
#include <string>
using namespace std;

/**
 * @class RegisterManager
 *
 * @brief Classe template che gestisce un registro.
 *
 * 
 */

template <template<typename, typename> class RegisterMap> /*devi passarmi una mappa template con 2 parametri Key e Elem, ci penso io a declinarli a string*/
class RegisterManager : public RegistrablePoolableCyclicCallableSkeleton
{
protected:
    void doService()
    {
        string* requestedOperation = (string*)(inputParameters.front())->getValue();
        inputParameters.pop_front();
        if(requestedOperation->compare("publish") == 0) editMap("publish");
        if(requestedOperation->compare("censor") == 0) editMap("censor");
        if(requestedOperation->compare("search") == 0) searchInMap();
        delete requestedOperation;
        //Se nessuno di questi if si attiva il registro non fa niente, alla fine risponde lista vuota e tutti contenti
        inputParameters.clear();
    }
    virtual void editMap(string command)
    {
        RegisterMap<string, string>* sharedRegister = SingletonObject< RegisterMap<string, string> >::getInstance(); //deve essere singleton!
        SerializableObjectList::iterator i = inputParameters.begin();
        while(i != inputParameters.end())
        {
            string* entry = (string*)(*i)->getValue();
            string key = entry->substr(0, entry->find_first_of('@'));
            string element = entry->substr(entry->find_first_of('@')+1);
            if(command.compare("publish") == 0)
            {
                sharedRegister->insertElement(key, element);
            }
            if(command.compare("censor") == 0)
            {
                sharedRegister->clearElement(key, element);
            }
            sharedRegister->print();
            delete entry;
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
        //TODO non size_type ma qualcos'altro!
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
