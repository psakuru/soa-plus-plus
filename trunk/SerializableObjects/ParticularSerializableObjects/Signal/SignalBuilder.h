#ifndef SIGNALBUILDER_H
#define SIGNALBUILDER_H

#include "../../SerializableObjectBuilder.h"

class SignalBuilder : public SerializableObjectBuilder
{
    public:
    	SignalBuilder();
    	~SignalBuilder();
        virtual SerializableObject* delegateBuilding(Type typeToBuild, uint64_t valueLength, void* value);
};

#endif // SIGNALBUILDER_H
