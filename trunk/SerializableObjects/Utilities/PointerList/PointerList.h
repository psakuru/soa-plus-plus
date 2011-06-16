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
	};

#endif // POINTERLIST_H
