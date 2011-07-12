class UnivocalNumberGenerator
{
private:
	unsigned int seed;
public:
	UnivocalNumberGenerator()
	{
		seed = 0;
	}
	getUnivocalNumber()
	{
		//P(mutex)
		unsigned int numberToReturn = seed;
		seed++;
		return numberToReturn;
		//V(mutex)
	}
};
