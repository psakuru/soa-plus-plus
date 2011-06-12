#ifndef GENERIC_SERIALIZABLE_REFERENCE_LAYER_H
#define GENERIC_SERIALIZABLE_REFERENCE_LAYER_H
#include "../SerializableObject.h"
#include <iostream>
using namespace std;

template <typename T>
class GenericSerializableReferenceLayer : public SerializableObject
	{
	protected:
		T& wrappedReference;
		bool userReference;
	public:
		GenericSerializableReferenceLayer() : wrappedReference(*(new T()))
			{
            cout << "Costruttore di default del GenericSerializableReferenceLayer" << endl;
			userReference = false;
			}
		GenericSerializableReferenceLayer(T& referenceToWrap) : wrappedReference(referenceToWrap)
			{
			userReference = true;
			}
		~GenericSerializableReferenceLayer()
			{
			if(!userReference) delete &wrappedReference;
			}
		void operator=(const SerializableObject& objectToCopy)
			{
		    const GenericSerializableReferenceLayer* castReference =
		    	dynamic_cast<const GenericSerializableReferenceLayer*>(&objectToCopy);
		    	//Lanciare eccezioni di dynamic_cast!
		    wrappedReference = castReference->wrappedReference;
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
