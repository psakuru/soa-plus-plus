#ifndef SERIALIZABLEOBJECT_H
#define SERIALIZABLEOBJECT_H


class SerializableObject
{
    public:
        virtual ~SerializableObject();
        virtual void operator=(const SerializableObject&) = 0;
        virtual uint64_t serialize(void* destinationBuffer) = 0;
        virtual void deserialize(void* bufferToUse) = 0;
};

#endif // SERIALIZABLEOBJECT_H
