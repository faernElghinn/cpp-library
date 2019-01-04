/*
 * Random.h
 *
 *  Created on: Aug 31, 2016
 *      Author: daniel
 */

#pragma once

#include <cstdint>
#include <cstring>
#include <string>
#include "Stringify.h"

namespace elladan {

class UUID
{
public:
    static UUID generateUUID();

    UUID();

    UUID (const UUID& other) {
        memcpy(_uuid, other._uuid, sizeof(_uuid));
    }

    bool operator!() const;

    inline int cmp(const UUID& other) const {
        return std::memcmp(_uuid, other._uuid, sizeof(_uuid));
    }
    inline bool operator==(const UUID& other) const { return cmp(other) == 0; }
    inline bool operator!=(const UUID& other) const { return cmp(other) != 0; }
    inline bool operator> (const UUID& other) const { return cmp(other) >  0; }
    inline bool operator< (const UUID& other) const { return cmp(other) <  0; }
    inline bool operator>=(const UUID& other) const { return cmp(other) >= 0; }
    inline bool operator<=(const UUID& other) const { return cmp(other) <= 0; }

    std::string toString() const;
    static UUID fromString(const std::string& str);

    inline uint8_t* getRaw() { return _uuid; }
    inline const uint8_t* getRaw() const { return _uuid; }
    inline size_t getSize() const { return sizeof(_uuid); }

private:
    uint8_t _uuid[16];

};

} // namespace elladan

namespace std {
std::string to_string(const elladan::UUID& ele);
}  // namespace std

template<>
elladan::UUID fromString<elladan::UUID>(std::string const&);
