#include "Functor.h"

Functor::Functor() {

}

void Functor::operator()(ServiceThread& thread) {

	thread.run();

}
