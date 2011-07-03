class GetList: public StreamStub {
public:
	GetList() :
		StreamStub("GetList", "127.0.0.1:4000") {

	}
	void operator()(ByteArray& list) {

		(*this) >> bufferList;

		bind();

		protocol();

	}
};
