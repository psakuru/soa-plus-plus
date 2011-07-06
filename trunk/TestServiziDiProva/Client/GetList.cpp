class GetList: public StreamStub {
public:
	GetList() :
		StreamStub("ImageRegister", "127.0.0.1:4000") {

	}
	void operator()(ByteArray& list) {

		(*this) << (string)"getList";

		(*this) >> bufferList;

		bind();

		protocol();

	}
};
