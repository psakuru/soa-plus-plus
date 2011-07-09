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
#include "../../Utilities/RegularExpressionChecker/RegularExpressionChecker.h"
#include <iostream>
#include <string>
using namespace std;

/**
 * @class RegisterManager
 *
 * @brief Classe template che gestisce un registro.
 *
 * Il RegisterManager è un RegistrablePoolableCyclicCallableSkeleton il cui servizio consiste nell' effettuare le operazioni di
 * registrazione e deregistrazione richieste.
 * Il protocollo di richiesta è : request := {oneof {commandPublish list parameterPublish}, {search parameterSearch}}; commandPublish := {oneof publish, censor};
 * parameterPublish := {serviceID@IP:port}; parameterSearch := {serviceID}.
 *
 */

template <template<typename, typename> class RegisterMap>
class RegisterManager : public RegistrablePoolableCyclicCallableSkeleton
{
protected:
    /**
     * Esegue l' operazione richiesta in base al comando ricevuto.
     */
    void doService()
    {
        string* requestedOperation = (string*)(inputParameters.front())->getValue();
        inputParameters.pop_front();
        if(requestedOperation->compare("publish") == 0) editMap("publish");
        if(requestedOperation->compare("censor") == 0) editMap("censor");
        if(requestedOperation->compare("search") == 0) searchInMap();
        delete requestedOperation;
        inputParameters.clear();
    }
    /**
     * Modifica la mappa in base al parametro command.
     */
    virtual void editMap(string command)
    {
        RegisterMap<string, string>* sharedRegister = SingletonObject< RegisterMap<string, string> >::getInstance();
        SerializableObjectList::iterator i = inputParameters.begin();
        while(i != inputParameters.end())
        {
            RegularExpressionChecker* serviceIDRegexChecker = SingletonObject<RegularExpressionChecker>::getInstance();
            serviceIDRegexChecker->setRegularExpression("\\w*\\((\\s(IN|INOUT)\\:\\s\\w*)*\\)\\@\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b\\:(4915[0-1]|491[0-4]\\d|490\\d\\d|4[0-8]\\d{3}|[1-3]\\d{4}|[2-9]\\d{3}|1[1-9]\\d{2}|10[3-9]\\d|102[4-9])"); //Matcha con serviceID( IN: int ... INOUT: double)@IP:port
            string* entry = (string*)(*i)->getValue();
            if(!serviceIDRegexChecker->checkForMatch(*entry)) return;
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
    }
    /**
     * Ricerca il servizio richiesto nella mappa e lo invia come output.
     */
    virtual void searchInMap()
    {
        cout << "Ricevuta una richiesta di ricerca: " << endl;
        RegisterMap<string, string>* sharedRegister = SingletonObject< RegisterMap<string, string> >::getInstance();
        SerializableObjectList::iterator i = inputParameters.begin();
        string key = *((string*)(*i)->getValue());
        cout << "Chiave di ricerca:: " << key << endl;
        string* searchResult = new string((*sharedRegister)[key]);
        cout << "Risultato della ricerca:: " << *searchResult << endl;
        outputParameters.push_back(new String(searchResult, false));
    }
public:
    RegisterManager() : Skeleton("register"), RegistrablePoolableCyclicCallableSkeleton("register") {}
    virtual void receiveParameters()
    {
        uint32_t* incomingParametersSizePointer =
            ((uint32_t*)socket->receiveMessage(sizeof(uint32_t)));
        uint32_t incomingParametersSize = *incomingParametersSizePointer;
        free(incomingParametersSizePointer);
        if((int)incomingParametersSize > 1024 || (int)incomingParametersSize <= 0)
        {
            throw DOSAttackInProgress();
        }
        SerializableObjectList* incomingParameters = new SerializableObjectList;
        for(uint32_t i = 0; i < (incomingParametersSize); i++)
        {
            inputParameters.push_back(new String);
        }
        for(uint32_t i = 0; i < incomingParametersSize; i++)
        {
            incomingParameters->push_back(receiveParameter());
        }
        SerializableObjectList::iterator i = inputParameters.begin();
        SerializableObjectList::iterator j = incomingParameters->begin();
        while(i != inputParameters.end())
        {
            *(*i) = *(*j); // In caso di type-mismatch lancia un' eccezione.
            i++;
            j++;
        }
        delete incomingParameters;
    }
    ~RegisterManager()
    {
        //SingletonObject< RegisterMap<string, string> >::destroyInstance();  // Elimina l' istanza Singleton.
        //SingletonObject<RegularExpressionChecker>::destroyInstance();  // Elimina l' istanza Singleton.
    }
};

#endif // REGISTERMANAGER_H
