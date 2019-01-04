/*
 * JsonDbTest.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: daniel
 */

#include <cstdlib>
#include <string>
#include <vector>

#include "../src/FileManipulator.h"
#include "Test.h"

static std::string test_folder_manip(){
    std::string retVal;

    system( "rm -rf /tmp/JsonUnitTest" ); // Clean previous test.
    createFolder("/tmp/JsonUnitTest/child/subchild"); // Create the folder hierarchy.
    if (system( "touch /tmp/JsonUnitTest/child/subchild/1.json") != 0)
        // Touch fail if parent don't exist.
        retVal += "\n Could not create file in created directory. Directory not created?";
    if (listFile("/tmp/JsonUnitTest/child/subchild/", ".json").size() != 1)
        retVal += "\n Directory does not have one file. Contaminated or could not read it?";

    system("touch /tmp/JsonUnitTest/child/subchild/2.json");
    system("touch /tmp/JsonUnitTest/child/subchild/3.json");
    system("touch /tmp/JsonUnitTest/child/subchild/4.json");
    system("touch /tmp/JsonUnitTest/child/subchild/5.txt");
    auto files = listFile("/tmp/JsonUnitTest/child/subchild/", ".json");

    bool found = false;
    for (auto& ite : files)
        found |= ite == "1.json";

    if (!found)
        // Test that the found filename are valid
        retVal += "\n Could not find 1.json in the file listing";

    found = false;
    for (auto& ite : files)
        found |= ite == "5.txt";
    if (found)
        // Test that the found filename are valid
        retVal += "\n Found file 5.txt while searching for only *json files";

    if (retVal.empty())
        system( "rm -rf /tmp/JsonUnitTest" ); // Cleanup
    return retVal;
}


int main(int argc, char **argv) {
    bool valid = true;
    EXE_TEST(test_folder_manip());
    return valid ? 0 : -1;
}

