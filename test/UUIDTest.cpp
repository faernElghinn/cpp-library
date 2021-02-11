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
   if (ud1 == udBlank) // Random uuid should not be blank.
      retVal += "\n Empty uuid is viewed as == to an random uuid";
   
   ud2 = UUID::generateUUID();
   if (ud1 == ud2) // Random uuid should not the same.
      retVal += "\n 2 random uuid are the same!";

   ud2 = UUID::fromString(ud1.toString());
   if (ud1 != ud2) // Validate exporting and re-importing value,
      retVal += "\n Regenerating uuid is seen as different!";

   const char asStr[] = "01234567-89ab-cdef-0123-456789abcdef";
   UUID ud3(asStr);
   if (ud3.toString() != asStr)
      retVal += std::string("\n Could not decode string, expected \n\t") + asStr + "\ngot : \n\t" + ud3.toString();

   std::vector<char> v = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
   UUID ud4(v);
   if (memcmp(ud4.getRaw(), v.data(), v.size() ) )
      retVal += "\n Could not decode char vector, expected 0 to 15, got : " + ud4.toString();

   return retVal;
}


int main(int argc, char **argv) {
    bool valid = true;
    EXE_TEST(test_uuid());
    return valid ? 0 : -1;
}

