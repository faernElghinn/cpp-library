/*
 * JsonDbTest.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: daniel
 */

#include "../src/Stringify.h"
#include "../src/FileManipulator.h"
#include "Test.h"

static std::string test_string_manip(){
    std::string retVal;

    auto token = tokenize("/1/2/3//5", "/");
    if (token.size() != 6)  retVal += "\n Could not tokenize : Invalid number of token";

    const std::string expected[] = {"", "1", "2", "3", "", "5" };

    for (int i = 0; i < 6; i++){
        if (token[i] != expected[i])
            retVal += "\n Could not tokenize : token does not match expected value ";
    }

    std::string entry = "/path/with/many//slashee//";
    std::string expect = "/path/with/many/slashee/";
    if (removeDoubleSlash(entry) != expect)
        retVal += "\n Invalid removeDoubleSlash";

    return retVal;
}



int main(int argc, char **argv) {
    bool valid = true;
    EXE_TEST(test_string_manip());
    return valid ? 0 : -1;
}

