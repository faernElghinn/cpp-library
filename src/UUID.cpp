/*
 * Random.h
 *
 *  Created on: Aug 31, 2016
 *      Author: daniel
 */

#include "UUID.h"
#include <cstdio>
#include <cassert>

#include "Random.h"
#include "Exception.h"

namespace elladan {

UUID::UUID (const std::string& str) {
   if (str.size() != 16 * 2 + 4) 
      throw Exception("Invalid UUID " + str);

   int o = 0;
   for (int i = 0; i < 16; i++) {
      if (str[i*2+o] == '-') o++;
      _uuid[i] = (uint8_t) stoi(str.substr(2*i+o, 2), 0, 16);
   }
}
UUID::UUID (std::vector<char>& d) {
   size_t l = std::min(d.size(), sizeof(_uuid));
   memcpy(_uuid, d.data(), l);
}
UUID::UUID (std::vector<uint8_t>& d) {
   size_t l = std::min(d.size(), sizeof(_uuid));
   memcpy(_uuid, d.data(), l);
}

UUID UUID::generateUUID(int version) {
   UUID uuid;


   if (version == 4) {
      for (auto && ite : uuid._uuid)
         ite = Random::get(UINT8_MAX);
      // Version 4 require a 4. Completely random UUID
      uuid._uuid[6] = (4 << 4) + uuid._uuid[6] & 0xf;
   }
   else
      throw Exception("Only UUIDv4 is implemented.");

   return uuid;
}

UUID::UUID() {
   memset(_uuid, 0, sizeof(_uuid));
}
UUID::UUID (const UUID& other){
   memcpy(_uuid, other._uuid, size);
}
UUID::UUID (UUID&& other){
   memcpy(_uuid, other._uuid, size);
}

UUID& UUID::operator=(const UUID& other){
   memcpy(_uuid, other._uuid, size);
   return *this;
}

bool UUID::operator!() const {
   uint8_t mask = 0;
   for (auto ite : _uuid)
      mask |= ite;
   return !mask;
}

int UUID::cmp(const UUID& other) const {
   return memcmp(_uuid, other._uuid, sizeof(_uuid));
}

std::string UUID::toString() const {
   char data[16 * 2 + 4 + 1];
   snprintf(data, sizeof(data),
         "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
         _uuid[0],  _uuid[1],  _uuid[2],  _uuid[3],
         _uuid[4],  _uuid[5],  _uuid[6],  _uuid[7],
         _uuid[8],  _uuid[9],  _uuid[10], _uuid[11],
         _uuid[12], _uuid[13], _uuid[14], _uuid[15]);
   return data;
}

UUID UUID::fromString(const std::string& str) {
   return UUID(str);
}

} /* namespace elladan */

namespace std {
std::string to_string(const elladan::UUID& ele) { return ele.toString(); }
}  // namespace std

template<>
elladan::UUID fromString<elladan::UUID>(const std::string& str){
   return elladan::UUID::fromString(str);
}
