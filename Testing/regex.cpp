#include "../RegularExpressionChecker/RegularExpressionChecker.h"
#include "../ObjectInterfaces/SingletonObject/SingletonObject.h"
using namespace std;

int main()
{
string IPAddress = "227.0.0.1:49151";
RegularExpressionChecker* checker = SingletonObject<RegularExpressionChecker>::getInstance();
checker->setRegularExpression("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b\\:(4915[0-1]|491[0-4]\\d|490\\d\\d|4[0-8]\\d{3}|[1-3]\\d{4}|[2-9]\\d{3}|1[1-9]\\d{2}|10[3-9]\\d|102[4-9])");
cout << checker->checkForMatch(IPAddress);
checker->setRegularExpression("abc");
cout << checker->checkForMatch("no");
return 0;
}

