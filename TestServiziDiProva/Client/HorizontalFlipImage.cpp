#include "../ServiceOrientedArchitecture/Service/Stub/StreamStub/StreamStub.h"

class HorizontalFlipImage: public StreamStub {
public:
	HorizontalFlipImage() :
		StreamStub("HorizontalFlipImage", "127.0.0.1:4000") {

	}
	void operator()(ByteArray& img, ByteArray& img2) {

		(*this) << img;

		(*this) >> img2;

		bind();
	}
};
