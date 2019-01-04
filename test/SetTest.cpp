/*
 * JsonDbTest.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: daniel
 */

#include "../src/Set.h"

#include <string>

#include "../src/Stringify.h"
#include "Test.h"

static std::string setToString(const std::set<int>& set) {
    std::string retVal = "{";

    for (auto ite : set) {
        retVal += std::to_string(ite);
        retVal += ",";
    }

    if (set.size())
       retVal.pop_back();

    retVal += "}";

    return retVal;
}

static bool cmpSet(const std::set<int>& left, const std::set<int>& right) {
    if (left.size() != right.size()) return false;

    auto li = left.begin();
    auto ri = right.begin();
    while (li != left.end() && ri != right.end()){
        if (*li != *ri) return false;
        ++li;
        ++ri;
    }
    return true;
}

static std::string test_inter() {
    std::string retVal;

    std::set<int> base = {0, 1, 2, 3, 4, 5};
    std::set<int> other = {1, 4, 6, 7};
    std::set<int> expected = {1, 4};

    std::set<int> result = intersect(base, other);

    if (!cmpSet(result, expected)){
        retVal += "\n Error intersecting set. Expected\n";
        retVal += setToString(expected);
        retVal += "\nGot\n";
        retVal += setToString(result);
    }

    return retVal;
}

static std::string test_diff() {
    std::string retVal;

    std::set<int> base = {0, 1, 2, 3, 4, 5};
    std::set<int> other = {1, 4, 6, 7};
    std::set<int> expected = {0, 2, 3, 5};

    std::set<int> result = difference(base, other);

    if (!cmpSet(result, expected)){
        retVal += "\n Error differencing set. Expected\n";
        retVal += setToString(expected);
        retVal += "\nGot\n";
        retVal += setToString(result);
    }

    return retVal;
}

static std::string test_keep_diff() {
    std::string retVal;

    std::set<int> base = {0, 1, 2, 3, 4, 5};
    std::set<int> other = {1, 4, 6, 7};
    std::set<int> expected = {0, 2, 3, 5};

    keep_difference(base, other);

    if (!cmpSet(base, expected)){
        retVal += "\n Error differencing set. Expected\n";
        retVal += setToString(expected);
        retVal += "\nGot\n";
        retVal += setToString(base);
    }

    return retVal;
}

static std::string test_keep_inter() {
    std::string retVal;

    std::set<int> base = {0, 1, 2, 3, 4, 5};
    std::set<int> other = {1, 4, 6, 7};
    std::set<int> expected = {1, 4};

    keep_intersect(base, other);

    if (!cmpSet(base, expected)) {
        retVal += "\n Error intersecting array. Expected\n";
        retVal += setToString(expected);
        retVal += "\nGot\n";
        retVal += setToString(base);
    }

    return retVal;
}


int main(int argc, char **argv) {
    bool valid = true;
    EXE_TEST(test_inter());
    EXE_TEST(test_keep_inter());
    EXE_TEST(test_diff());
    EXE_TEST(test_keep_diff());
    return valid ? 0 : -1;
}

