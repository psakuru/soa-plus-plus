/**
 * @file GenericSerializableRefenceLayer.h
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

#ifndef GENERIC_SERIALIZABLE_REFERENCE_LAYER_H
#define GENERIC_SERIALIZABLE_REFERENCE_LAYER_H
#include "../SerializableObject.h"
#include <iostream>
#include <typeinfo>
#include "../DeserializationStrategies/Exceptions/IncompatibleTypes.h"
using namespace std;

/**
 * @class GenericSerializableRefenceLayer
 *
 * @brief Classe template che implementa parte dei metodi esposti dall' intefaccia SerializableObject.
 * 
 * Il layer è pensato per rendere serializzabili dei riferimenti ad oggetti locali.
 * I metodi esposti da SerializableObject ed implementati dal layer sono indipendenti dal particolare tipo del riferimento gestito.
 * I rimanenti, che invece dipendono dal particolare tipo, verranno implementati da classi derivate dal layer secondo strategie opportune.
 *
 */

template <typename T>
class GenericSerializableReferenceLayer : public SerializableObject
{
protected:
	/**
	 * Riferimento gestito. 
	 */
    T& wrappedReference;
	/**
	 * Indica se il riferimento è condiviso. In caso negativo, il riferimento può essere cancellato dal distruttore.
	 */
    bool sharedReference;
public:
	/**
	 * Costruttore di default. Crea un oggetto del tipo opportuno e setta a false il flag sharedReference.
     */
    GenericSerializableReferenceLayer() : wrappedReference(*(new T()))
    {
        sharedReference = false;
    }
	/**
	 * Costruttore. Assegna al riferimento wrappato il parametro referenceToWrap.
	 * Inoltre setta il flag sharedReference, lasciando l' ownership del riferimento al chiamante.
	 *
	 * @param referenceToWrap 
     */
    GenericSerializableReferenceLayer(T& referenceToWrap) : wrappedReference(referenceToWrap)
    {
        sharedReference = true;
    }
	/**
	 * Costruttore. Assegna al riferimento wrappato il parametro referenceToWrap.
	 * Inoltre setta il flag sharedReference secondo il parametro shared.
	 * Si utilizza per decidere esplicitamente se lasciare all' oggetto serializzabile l' ownership del riferimento.
	 *
	 * @param referenceToWrap
	 * @param shared
	 *
	 * @pre Il parametro referenceToWrap deve essere stato creato attraverso l'operatore new altrimenti durante 
	 * l' esecuzione del distruttore potrebbe verificarsi segmentation fault.
     */
    GenericSerializableReferenceLayer(T* referenceToWrap, bool shared) : wrappedReference(*referenceToWrap)
    {
        sharedReference = shared;
    }
	/**
	 * Distruttore. Se il riferimento wrappato non è condiviso, la memoria da esso occupata viene liberata.
     */
    ~GenericSerializableReferenceLayer()
    {
        if(!sharedReference)
        {
            delete &wrappedReference;
        }
    }
	/**
	 * Operatore di assegnamento. Prima di effettuare la copia dell' oggetto passato come parametro, si confrontano i tipi. 
	 * Se objectToCopy è di un tipo differente dall' oggetto serializzabile sul quale viene invocato l' operatore, viene lanciata un' eccezione di tipo IncompatibleTypes.
	 *
	 * @param objectToCopy
	 *
	 * @pre Il parametro objectToCopy deve avere lo stesso tipo dell' oggetto serializzabile sul quale viene invocato l' operatore.
     */
    void operator=(const SerializableObject& objectToCopy)
    {
        if(this->getType() == objectToCopy.getType())
        {
            const GenericSerializableReferenceLayer* castReference = dynamic_cast<const GenericSerializableReferenceLayer*>(&objectToCopy);
            wrappedReference = castReference->wrappedReference;
        }
        else
        {
            throw IncompatibleTypes();
        }
    }
	/**
	 * Operatore di assegnamento. Prima di effettuare la copia dell' oggetto passato come parametro, si confrontano i tipi. 
	 * Se objectToCopy è di un tipo differente dall' oggetto serializzabile sul quale viene invocato l' operatore, viene lanciata un' eccezione di tipo IncompatibleTypes.
	 *
	 * @param objectToCopy
	 *
	 * @pre Il parametro objectToCopy deve avere lo stesso tipo dell' oggetto serializzabile sul quale viene invocato l' operatore.
     */
    void setValue(void* valueToSet)
    {
        wrappedReference = *((T*)(valueToSet));
    }
    void* getValue()
    {
        return new T(wrappedReference);
    }
};
#endif //GENERIC_SERIALIZABLE_REFERENCE_LAYER_H
