#include <list>
#include <iostream>
using namespace std;

template <typename T>
class PointerList : public list<T>
	{
	public:
		virtual ~PointerList()
			{
			typename list<T>::iterator i = this->begin();
			for(; i != this->end(); i++)
				{
				delete (*i);
				}
			}
		virtual void clear()
			{
			typename list<T>::iterator i = this->begin();
			while(i != this->end())
				{
				cout << "Eliminato dalla lista" << endl;
			    delete (*i); //Fa la delete di ciò che è puntato
			    i++;
			    this->pop_front(); //Fa fuori il puntatore in lista
			    }
			}
	};

class base
	{
	public:
		virtual ~base()
			{
			cout << "Distruttore di base" << endl;
			}
		virtual void whoAmI() = 0;
	};

template <typename T>
class derivataPrima : public base
	{
	protected:
	T& membro;
	bool userReference;
	public:
	derivataPrima() : membro(*(new T))
		{
		userReference = false;
		}
	derivataPrima(T& reference) : membro(reference)
		{
		userReference = true;
		}
	virtual ~derivataPrima()
		{
		cout << "Distruttore derivataPrima" << endl;
		if(!userReference)
			{
			delete &membro;
			cout << "Riferimento wrappato eliminato" << endl;
			}
		else
			{
			cout << "Riferimento wrappato NON eliminato" << endl;
			}
		}
	};

class derivataSeconda : public derivataPrima<int>
	{
	public:
	derivataSeconda(){}
	derivataSeconda(int& val) : derivataPrima<int>(val){}
	virtual ~derivataSeconda()
		{
		cout << "Distruttore derivataSeconda" << endl;
		}
	};

int main()
	{
		{
		PointerList<int*> outputParameters;
		PointerList<int*> inputParameters;
		outputParameters.push_back(new int(1));
		outputParameters.push_back(new int(2));
		outputParameters.push_back(new int(3));
		outputParameters.push_back(new int(4));
		PointerList<int*>::iterator k = outputParameters.begin();
		cout << "outputParameters:" << endl;
		for(; k!= outputParameters.end(); k++){ cout << *(*k)<< endl;}
		inputParameters.push_back(new int(5));
		inputParameters.push_back(new int(6));
		inputParameters.push_back(new int(7));
		inputParameters.push_back(new int(8));
		PointerList<int*>::iterator l = inputParameters.begin();
		cout << "inputParameters:" << endl;
		for(; l!= inputParameters.end(); l++){ cout << *(*l) << endl;}
		int outputParametersSize = (int)outputParameters.size();
		outputParameters.splice(outputParameters.end(), inputParameters);
		k = outputParameters.begin();
		cout << "outputParameters:" << endl;
		for(; k!= outputParameters.end(); k++){ cout << *(*k)<< endl;}
		PointerList<int*>::iterator i = outputParameters.begin();
		advance(i, outputParametersSize);
		PointerList<int*>::iterator j = outputParameters.end();
		inputParameters.splice(inputParameters.begin(), outputParameters, i, j);
		l = inputParameters.begin();
		cout << "inputParameters:" << endl;
		for(; l!= inputParameters.end(); l++){ cout <<*(*l)<< endl;}
		inputParameters.clear();
		}
	return 0;
	}
