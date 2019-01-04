/*
 * VMapTest.cpp
 *
 *  Created on: Jul 20, 2018
 *      Author: daniel
 */


#include "../src/VMap.h"

#include <iterator>
#include <sstream>
#include <string>

#include "Test.h"


static std::string test_vMap(){
   std::stringstream ss;

   VMap<int, std::string> map;

   if (!map.insert(1, "patate"))
      ss << "\n First key marked as already in map";

   map[2] = "boto";

   if (map.insert(1, "toto"))
      ss << "\n First key not marked as already in map";

   if (!map.count(1))
      ss << "\n First key not counted in map";

   if (!map.count(2))
      ss << "\n Second key not counted in map";

   if (map.find(1) == map.end())
      ss << "\n Second key not findable in map";

   if (map.find(2) == map.end())
      ss << "\n Second key not findable in map";

   if (map.find(1)->second != "patate")
      ss << "\n Second key not set rightly in map";

   if (map.find(2)->second != "boto")
      ss << "\n Second key not rightly in map";

   if (map[1] != "patate")
      ss << "\n Second key [] not set rightly in map";

   if (map[2] != "boto")
      ss << "\n Second key [] not rightly in map";

   map[1] = "grecque";
   if (map[1] != "grecque")
      ss << "\n First key [] set not working";

   map.erase(1);
   if (map.count(1))
      ss << "\n First key not removed";

   map[1] = "cuite";
   if (map.find(1) == map.end() || map[1] != "cuite")
      ss << "\n First key not added with []";

   return ss.str();
}



int main(int argc, char **argv) {
    bool valid = true;
    EXE_TEST(test_vMap());
    return valid ? 0 : -1;
}

