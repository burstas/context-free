// Rand64.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2008-2012 John Horigan - john@glyphic.com
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
// 
// John Horigan can be contacted at john@glyphic.com or at
// John Horigan, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//


#ifndef INCLUDE_RAND48_H
#define INCLUDE_RAND48_H

#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif

#include <stdint.h>

// This class  implements the xorshift64* PRNG.
class Rand64 {
public:
    enum e_consts : uint64_t {
        RAND64_MULT = 2685821657736338717ULL,
        RAND64_SEED = 0x3DF41234ABCD330EULL
    };
    
    uint64_t mSeed;
    static Rand64   Common;
    
    Rand64() : mSeed(RAND64_SEED) { }
    Rand64(uint64_t seed) : mSeed(seed) { }
    
    // Return double in [0,1)
    double getDoubleLower(bool bump = true);
    
    // Return double in (0,1]
    double getDoubleUpper(bool bump = true);
    
    // Return long in [LONG_MIN,LONG_MAX]
    long getLong(bool bump = true);
    
    // Return long in [0,LONG_MAX]
    long getPositive(bool bump = true);
    
    // Return ulong in [0,ULONG_MAX]
    unsigned long getUnsigned(bool bump = true);
    
    void seed(uint64_t seed);
    void init();
    
    Rand64& operator^=(const Rand64& r)
    {
        mSeed ^= r.mSeed;
        return *this;
    };
    bool operator==(const Rand64& r)
    {
        return mSeed == r.mSeed;
    };
    void xorString(const char* t, int& i);
    void xorChar(unsigned char c, unsigned i);
    void bump();
};

#endif  // INCLUDE_RAND48_H
    
    
