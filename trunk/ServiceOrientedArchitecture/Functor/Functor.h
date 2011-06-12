#ifndef FUNCTOR_H
#define FUNCTOR_H

#include "ServiceThread.h"

class Functor {

public:
	void operator()(ServiceThread& thread);
	Functor();

};

#endif // FUNCTORH
