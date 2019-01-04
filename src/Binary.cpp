/*
 * Binary.cpp
 *
 *  Created on: Oct 31, 2017
 *      Author: daniel
 */

#include "Binary.h"

#include <stdlib.h>
#include <cassert>
#include <cstring>
#include <sstream>

#include "Stringify.h"

namespace elladan {

Binary::Binary(size_t s) 
{
    data.resize(s,0);
}

Binary::Binary(void* d, size_t s) 
{ 
    data.resize(s,0);
    memcpy(data.data(), d, s);
}

Binary::Binary(const std::string& str) 
: Binary((str.size() + 1) / 2) 
{
    const char* inp = str.c_str();
    auto dst = data.data();

    for (int i = 0; i < data.size() - 1; i++)
        *dst++ = (charToHex(*inp++, 16) << 4) + charToHex(*inp++, 16);

    *dst = charToHex(*inp++, 16) << 4;
    if ((str.size() & 1) == 0)
        *dst += charToHex(*inp++, 16);
}

std::string Binary::toHex() const {
    std::stringstream str;

    for (int i = 0; i < data.size(); ++i)
        str << hexToChar(data[i]);

    return str.str();
}

Binary Binary::copy() const{
    return Binary((void*)data.data(), data.size());
}

int Binary::cmp(const Binary& rhs) const {
    if (size() != rhs.size()) return size() - rhs.size();
    return memcmp(data.data(), rhs.data.data(), size());
}

bool Binary::operator ==(const Binary& rhs) const { return cmp(rhs) == 0; }
bool Binary::operator !=(const Binary& rhs) const { return cmp(rhs) != 0; }
bool Binary::operator  <(const Binary& rhs) const { return cmp(rhs)  < 0; }
bool Binary::operator <=(const Binary& rhs) const { return cmp(rhs) <= 0; }
bool Binary::operator  >(const Binary& rhs) const { return cmp(rhs)  > 0; }
bool Binary::operator >=(const Binary& rhs) const { return cmp(rhs) >= 0; }

}  // namespace elladan


namespace std{
std::string to_string(const elladan::Binary& binary) { return binary.toHex(); }
}
