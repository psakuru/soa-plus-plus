#include <iostream>
#include "RegularExpressionChecker.h"

RegularExpressionChecker::RegularExpressionChecker() : unset(true) {}

RegularExpressionChecker::RegularExpressionChecker(string regularExpressionToSet)
{
    regularExpression = regularExpressionToSet;
    unset = false;
}

bool RegularExpressionChecker::setRegularExpression(string regularExpressionToSet)
{
    if(unset)
    {
        regularExpression = regularExpressionToSet;
        unset = false;
        return true;
    }
    return false;
}

bool RegularExpressionChecker::checkForMatch(string stringToCheck)
{
    return (unset)? false : boost::regex_match(stringToCheck, regularExpression);
}

RegularExpressionChecker::~RegularExpressionChecker() {}
