#include "RegularExpressionChecker.h"

RegularExpressionChecker::RegularExpressionChecker() : unset(true) {}

RegularExpressionChecker::RegularExpressionChecker(string regularExpressionToSet)
{
    regularExpression = regularExpressionToSet;
    unset = false;
}

void RegularExpressionChecker::setRegularExpression(string regularExpressionToSet)
{
    if(unset)
    {
        regularExpression = regularExpressionToSet;
        unset = false;
    }
}

bool RegularExpressionChecker::checkForMatch(string stringToCheck)
{
    return boost::regex_match(stringToCheck, regularExpression);
}
