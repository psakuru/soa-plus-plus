g++ -g newClient.cpp ../TcpIpSocket/TcpIp*.cpp ../SerializableObjects/SerializationStrategies/IntegerSerializationStrategy/*.cpp ../SerializableObjects/*.cpp ../SerializableObjects/DeserializationStrategies/*.cpp ../SerializableObjects/Utilities/ByteArray/*.cpp ../SerializableObjects/SerializationStrategies/RealSerializationStrategy/*.cpp ../SerializableObjects/SerializationStrategies/RawByteBufferSerializationStrategy/*.cpp ../SerializableObjects/SerializationStrategies/StringSerializationStrategy/*.cpp ../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/*.cpp ../SerializableObjects/SerializationStrategies/SignalSerializationStrategy/ParticularSignals/BadRequestSerializationStrategy/*.cpp ../ServiceOrientedArchitecture/Service/*.cpp ../ServiceOrientedArchitecture/Service/Stub/*.cpp ../ServiceOrientedArchitecture/Service/Stub/StreamStub/*.cpp -Wall -lboost_thread -lpthread -o newClient
