/*
 * JsonDbTest.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: daniel
 */

#include "../src/Random.h"
#include "Test.h"

static std::string test_random(){
    std::string retVal;

    unsigned int now;
    unsigned int last = 0;
    unsigned int same = 0;

    for (int i = 0; i < 10000; i++) {
        now = Random::get(1000);
        if (now >= 1000)
            retVal += "\n Random returned a value over the max";

        same += now == last;
        last = now;
    }

    if (same >= 100)
        retVal += "\n Got the same number many time in a row. Unlucky of not random?";

    std::string str = Random::generateString(64);
    if (str.size() != 64)
        retVal += "\n Got the wrong number of character in random string";
    for (auto ite : str) {
        if (!((ite >= 'a' && ite <= 'z') ||
              (ite >= 'A' && ite <= 'Z') ||
              (ite >= '0' && ite <= '9') ))
        retVal += "\n Got a value not in valid string range?";
    }

    return retVal;
}


int main(int argc, char **argv) {
    bool valid = true;
    EXE_TEST(test_random());
    return valid ? 0 : -1;
}

