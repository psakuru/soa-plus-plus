#ifndef REGULAREXPRESSIONCHECKER_H
#define REGULAREXPRESSIONCHECKER_H

#include <boost/regex.hpp>
#include <string>
using namespace std;

class RegularExpressionChecker
{
private:
    bool unset;
    boost::regex regularExpression;
public:
    RegularExpressionChecker();
    RegularExpressionChecker(string regularExpressionToSet);
    void setRegularExpression(string regularExpressionToSet);
    bool checkForMatch(string stringToCheck);
};

#endif // REGULAREXPRESSIONCHECKER_H
