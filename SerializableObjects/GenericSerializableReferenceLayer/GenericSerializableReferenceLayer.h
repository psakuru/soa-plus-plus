#ifndef GENERIC_SERIALIZABLE_REFERENCE_LAYER_H
#define GENERIC_SERIALIZABLE_REFERENCE_LAYER_H
#include "../SerializableObject.h"
#include <iostream>
#include <typeinfo>
#include <stdexcept>
using namespace std;

template <typename T>
class GenericSerializableReferenceLayer : public SerializableObject
	{
	protected:
		T& wrappedReference;
		bool sharedReference;
	public:
		GenericSerializableReferenceLayer() : wrappedReference(*(new T()))
			{
            //cout << "Costruttore di default del GenericSerializableReferenceLayer" << endl;
			sharedReference = false;
			}
		GenericSerializableReferenceLayer(T& referenceToWrap) : wrappedReference(referenceToWrap)
			{
			sharedReference = true;
			}
        GenericSerializableReferenceLayer(T* referenceToWrap, bool shared) : wrappedReference(*referenceToWrap)
			{
			sharedReference = shared;
			}
		~GenericSerializableReferenceLayer()
			{
            //cout << "Distruttore del GenericSerializableReferenceLayer" << endl;
			if(!sharedReference)
			{
			    delete &wrappedReference;
			}
			}
		void operator=(const SerializableObject& objectToCopy)
			{
            if(this->getType() == objectToCopy.getType())
            {
                const GenericSerializableReferenceLayer* castReference =
		    	dynamic_cast<const GenericSerializableReferenceLayer*>(&objectToCopy);
                cout << "Stesso tipo! " << (typeid(wrappedReference)).name() << "==" << (typeid(castReference->wrappedReference)).name() << endl;
                wrappedReference = castReference->wrappedReference;
            }
            else
            {
                runtime_error incompatibleTypes("Incompatible types.");
                throw incompatibleTypes;
            }
		    }
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
