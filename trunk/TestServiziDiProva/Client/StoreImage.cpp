/*
 * ImageManipulator.cpp
 *
 *  Created on: 03/lug/2011
 *      Author: davidesilvestri
 */
class StoreImage: public StreamStub {
public:
	StoreImage() :
		StreamStub("ImageRegister", "127.0.0.1:4000") {

	}
	void operator()(string& name, ByteArray& img) {

		(*this) << (string)"storeImage";

		(*this) << name;

		(*this) << img;

		bind();

		protocol();

	}
};
