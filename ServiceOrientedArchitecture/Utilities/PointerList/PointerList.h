#ifndef POINTERLIST_H
#define POINTERLIST_H

#include <list>
using namespace std;

template <typename T>
class PointerList : public list<T>
{
public:
    virtual ~PointerList()
    {
        typename list<T>::iterator i = this->begin();
        for(; i != this->end(); i++)
        {
            delete (*i);
        }
    }
    virtual void clear()
    {
        typename list<T>::iterator i = this->begin();
        while(i != this->end())
        {
            delete (*i); // Elimina l' oggetto puntato.
            i++;
            this->pop_front(); // Pop di un puntatore, non viene eliminato l' oggetto puntato.
        }
    }
	virtual void popPointers()
	{
		int iterationsToEmptyList = (int)size();
		for(int i = 0; i < iterationsToEmptyList; i++)
		{
			this->pop_front(); // Pop di un puntatore, non viene eliminato l' oggetto puntato.
		}
	}
};

#endif // POINTERLIST_H
