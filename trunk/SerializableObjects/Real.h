#ifndef REAL_H
#define REAL_H


class Real : public SerializableObject
{
    private:
        double& value; //Per il futuro: riportare in notazione mantissa ed esp, a grandezza nota
    public:
        /** Default constructor */
        Real(double& valueToSet);
        /** Default destructor */
        ~Real();
        void operator=(const SerializableObject& objectToCopy);
        uint64_t serialize((void*)& destinationBuffer);
        void deserialize(void* bufferToUse);
};

#endif // REAL_H
