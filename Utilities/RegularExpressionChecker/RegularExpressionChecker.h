/**
 * @file RegularExpressionChecker.h
 * @author  Sacco Cosimo <cosimosacco@gmail.com>, Silvestri Davide <davidesil.web@gmail.com>
 *
 * @section LICENSE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef REGULAREXPRESSIONCHECKER_H
#define REGULAREXPRESSIONCHECKER_H

#include <boost/regex.hpp>
#include <string>
using namespace std;


/**
 * @class RegularExpressionChecker
 *
 * @brief Gestisce le espressioni regolari.
 *
 * RegularExpressionChecker gestisce le espressioni regolari.
 *
 */

class RegularExpressionChecker
{
private:
    bool unset;
    boost::regex regularExpression;
public:
    RegularExpressionChecker();
    RegularExpressionChecker(string regularExpressionToSet);
    bool setRegularExpression(string regularExpressionToSet);
	/**
	 * Controlla se la stringa passata come argomento soddisfa l' espressione regolare regularExpression.
	 *
	 */
    bool checkForMatch(string stringToCheck);
    ~RegularExpressionChecker();
};

#endif // REGULAREXPRESSIONCHECKER_H
