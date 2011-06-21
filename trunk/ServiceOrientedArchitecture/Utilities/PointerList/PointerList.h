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
            delete (*i); //Fa la delete di ciò che è puntato
            i++;
            this->pop_front(); //Fa fuori il puntatore in lista
        }
    }
};

#endif // POINTERLIST_H
