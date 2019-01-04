/*
 * Random.h
 *
 *  Created on: Aug 31, 2016
 *      Author: daniel
 */

#include "Random.h"

namespace elladan {

::std::random_device Random::_src;

unsigned int Random::get(int max){
    ::std::uniform_int_distribution<int> dist(0, max-1);
    return dist(_src);
}
::std::string Random::generateString(int length){
    static const char seq_start[] = {'0', 'A'-10, 'a'-10-26};
    ::std::string result;
    ::std::uniform_int_distribution<int> dist(0, 2 * 26 + 10 - 1);

    while (length--) {
        int r = dist(_src);
        int offset = r < 10 ? 0 : (r < 36 ? 1 : 2);
        result.push_back(r+seq_start[offset]);
    }

    return result;
}


} /* namespace elladan */

