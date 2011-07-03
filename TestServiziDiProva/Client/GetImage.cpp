class GetImage: public StreamStub {
public:
	StoreImage() :
		StreamStub("GetImage", "127.0.0.1:4000") {

	}
	void operator()(string& name, ByteArray& img) {

		(*this) << name;

		(*this) >> img;

		bind();

		protocol();

	}
};
