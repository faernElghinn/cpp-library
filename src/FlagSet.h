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
 * Manage a list of flags.
 *
 * Contrary to BitSet, expect the flag to be directly manipulated.
 * You can thus set, clear and test multiple flag at the same time.
 */
class FlagSet{
public:
    FlagSet(){ _flags = 0; }
    FlagSet(uint64_t idx) { _flags = idx; }
    FlagSet(const FlagSet& idx) { _flags = idx._flags; }
    inline bool test(uint64_t idx) const { return _flags & idx; }
    inline void set(uint64_t idx) { _flags |= idx; }
    inline void clear(uint64_t idx) { _flags &= ~idx; }
    inline void clear() { _flags = 0;}
    inline uint64_t& rawFlags() {return _flags;}
protected:
    uint64_t _flags;
};


} // namespace elladan
