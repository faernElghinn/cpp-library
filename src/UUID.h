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
   static constexpr size_t size = 16;
    static UUID generateUUID();

    UUID();
    UUID (const UUID& other);
    UUID (UUID&& other);
    ~UUID() = default;
    constexpr UUID& operator=(const UUID& other){
        memcpy(_uuid, other._uuid, size);
        return *this;
    }

    UUID (const std::string& );
    UUID (std::vector<char>& );

    bool operator!() const;

    int cmp(const UUID& other) const;
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
    inline constexpr size_t getSize() const { return size; }
    static constexpr size_t getStringSize() { return size*2+4; }

private:
    uint8_t _uuid[size];
};

} // namespace elladan

namespace std {
std::string to_string(const elladan::UUID& ele);
}  // namespace std

template<>
elladan::UUID fromString<elladan::UUID>(std::string const&);
