/**
 * @file UnivocalNumberGenerator.h
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

#ifndef UNIVOCALNUMBERGENERATOR_H
#define UNIVOCALNUMBERGENERATOR_H
#include <boost/thread/mutex.hpp>

class UnivocalNumberGenerator
{
private:
	unsigned int seed;
	boost::mutex mutex;
public:
	UnivocalNumberGenerator()
	{
		seed = 0;
	}
	unsigned int getUnivocalNumber()
	{
		boost::lock_guard<boost::mutex> lock(mutex);
		unsigned int numberToReturn = seed;
		seed++;
		return numberToReturn;
	}
};

#endif
