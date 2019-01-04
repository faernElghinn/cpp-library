/*
 * FlagSet.h
 *
 *  Created on: Jun 21, 2017
 *      Author: daniel
 */

#pragma once

#include <cstdint>

namespace elladan {

/**
 * Bitset keep a list of up to 64 bits.
 * Each bits can be set and cleared.
 *
 * Contrary to FlagSet, this expect you to index which bit you want to set.
 * As thus, you can test & set only one bit at the time.
 */

class BitSet{
public:
    BitSet(){_flags = 0;}
    BitSet(const BitSet& idx) { _flags = idx._flags; }
    inline bool test(uint64_t idx) const { return _flags & (1 << idx); }
    inline void set(uint64_t idx) { _flags |= (1 << idx); }
    inline void clear(uint64_t idx) { _flags &= ~(1 << idx); }
    inline void clear() { _flags = 0;}
    inline uint64_t getRawFlags() {return _flags;}
    inline void setRawFlags(uint64_t val) { _flags = val; }
protected:
    uint64_t _flags;
};


} // namespace elladan
