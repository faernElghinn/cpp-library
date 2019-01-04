/*
 * JsonDbTest.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: daniel
 */

#include <set>
#include <string>

#include "../src/BitSet.h"
#include "../src/FlagSet.h"
#include "Test.h"


static std::string test_bitset() {
    std::string retVal;

    enum{
        ST = 0,
        ND = 1,
        TR = 2,
        TH = 4,
    };

    BitSet bs;

    bs.set(ST);
    bs.set(TR);

    if (bs.test(ND))
        retVal += "\n Found an unset value ";

    if (!bs.test(ST))
        retVal += "\n Could not find a set value ";

    bs.clear(TR);
    if (bs.test(TR))
        retVal += "\n Found value after clearing it";
    if (!bs.test(ST))
        retVal += "\n Could not find a set value ";

    bs.clear();
    if (bs.test(ST))
        retVal += "\n Found value after reset";

    return retVal;
}

static std::string test_flagset() {
    std::string retVal;

    enum{
        ST = 1 << 0,
        ND = 1 << 1,
        TR = 1 << 2,
        TH = 1 << 3,
    };

    FlagSet fs;

    fs.set(ST | TR);

    if (fs.test(ND))
        retVal += "\n Found an unset value ";

    if (!fs.test(ST))
        retVal += "\n Could not find a set value ";

    fs.clear(TR);
    if (fs.test(TR))
        retVal += "\n Found value after clearing it";
    if (!fs.test(ST))
        retVal += "\n Could not find a set value ";

    fs.clear();
    if (fs.test(ST))
        retVal += "\n Found value after reset";

    return retVal;
}



int main(int argc, char **argv) {
    bool valid = true;
    EXE_TEST(test_bitset());
    EXE_TEST(test_flagset());
    return valid ? 0 : -1;
}

