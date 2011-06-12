#ifndef FUNCTOR_H
#define FUNCTOR_H

#include "../ServiceThread/ServiceThread.h"

class Functor {

public:
	void operator()(ServiceThread& thread);
	Functor();

};

#endif // FUNCTORH
