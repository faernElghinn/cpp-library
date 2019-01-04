/*
 * JsonDbTest.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: daniel
 */

#include "../src/UUID.h"

#include "Test.h"

using namespace elladan;

static std::string test_uuid(){
    std::string retVal;

    UUID udBlank;
    UUID ud1;
    UUID ud2;
    if (ud1 != ud2) // Empty uuid must match.
        retVal += "\n Empty uuid are view as different";

    ud1 = UUID::generateUUID();
    ud2 = UUID::generateUUID();
    if (ud1 == udBlank) // Random uuid should not be blank.
        retVal += "\n Empty uuid is viewed as == to an random uuid";
    if (ud1 == ud2) // Random uuid should not be blank.
        retVal += "\n 2 random uuid are the same!";

    ud2 = UUID::fromString(ud1.toString());
    if (ud1 != ud2) // Validate exporting and re-importing value,
        retVal += "\n Regenerating uuid is seen as different!";

    return retVal;
}


int main(int argc, char **argv) {
    bool valid = true;
    EXE_TEST(test_uuid());
    return valid ? 0 : -1;
}

