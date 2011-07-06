class RotateImage: public StreamStub {
public:
	RotateImage() :
		StreamStub("RotateImage", "127.0.0.1:4000") {

	}
	void operator()(int& direction, ByteArray& img, ByteArray& img2) {

		(*this) << direction;

		(*this) << img;

		(*this) >> img2;

		bind();
	}
};
