//
//  ArchAbstractionPointer.h
//  absrtactArchPointer
//
//  Created by Axis on 2/23/16.
//  Copyright © 2016 Axis. All rights reserved.
//

#ifndef ArchAbstractionPointer_h
#define ArchAbstractionPointer_h

#include <stdint.h>
#include <libkern/OSByteOrder.h>

#ifdef __OPTIMIZE__
#define INLINE __attribute__((always_inline))
#else
#define INLINE
#endif

class BigEndian
{
public:
    //int16
    static uint16_t get16(const uint16_t& from) INLINE { return OSReadBigInt(&from, 0);}
    static void set16(uint16_t& info, uint16_t value) INLINE { OSWriteBigInt16(&info, 0, value);}

    //int32
    static uint32_t get32(const uint32_t& from) INLINE { return OSReadBigInt32(&from, 0); }
    static void set32(uint32_t& info, uint32_t value) INLINE { OSWriteBigInt32(&info, 0, value); }

    //int64
    static uint64_t get64(const uint64_t& from) INLINE { return OSReadBigInt64(&from, 0); }
    static void set64(uint64_t& info, uint64_t value) INLINE { OSWriteBigInt64(&info, 0, value); }

    //bits
    static uint32_t getBits(const uint32_t& from, uint8_t firstBit, uint8_t bitCount)
    {
        return getBitsRaw(get32(from), firstBit, bitCount);
    }

    static void setBits(uint32_t& info, uint32_t value, uint8_t firstBit, uint8_t bitCount)
    {
        uint32_t tmp = get32(info);
        setBitsRaw(tmp, value, firstBit, bitCount);
    }

    //raw
    static uint32_t getBitsRaw(const uint32_t& from, uint8_t firstBit, uint8_t bitCount) INLINE
    {
        return ((from>>(32-firstBit-bitCount)) & ((1<<bitCount)-1));
    }

    static void setBitsRaw(uint32_t& info, uint32_t value, uint8_t firstBit, uint8_t bitCount) INLINE
    {
        uint32_t tmp = info;
        const uint32_t mask = ((1<<bitCount)-1);
        tmp &= ~(mask<<(32-firstBit-bitCount));     //将firstBit~ bitCount的字段清零
        tmp |= ((value&mask)<<(32-firstBit-bitCount));
        info = tmp;
    }

    enum { little_endian = 0 };
};

class LittleEndian
{
public:
    //16 bits
    static uint16_t get16(const uint16_t& from) INLINE {return OSReadLittleInt16(&from, 0);}
    static void set16(uint16_t& info, uint16_t value) INLINE {OSWriteLittleInt16(&info, 0, value);}

    static uint32_t get32(const uint32_t& from) INLINE {return OSReadLittleInt32(&from, 0);}
    static void set32(uint32_t& info, uint32_t value) INLINE { OSWriteLittleInt32(&info, 0, value); }

    static uint64_t get64(const uint64_t& from) INLINE {return OSReadLittleInt64(&from, 0);}
    static void set64(uint64_t& info, uint64_t value) INLINE { OSWriteLittleInt64(&info, 0, value); }

    static uint32_t getBitRaw(const uint32_t& from, uint8_t firstBit, uint8_t bitCount) INLINE
    {
        return (from>>firstBit) & ((1<<bitCount)-1);
    }

    static void setBitRaw(uint32_t& from, uint32_t value, uint8_t firstBit, uint8_t bitCount)
    {
        uint32_t tmp = from;
        const uint32_t mask = (1<<bitCount)-1;      //set mask
        tmp &= ~(mask << firstBit);                 //set zero
        tmp |= (value&mask) << firstBit;
        from = tmp;
    }

    enum { little_endian = 1 };
};

template <typename _E>
class Pointer32
{
public:
    typedef uint32_t uint_t;
    typedef int32_t  sint_t;
    typedef _E E;

    static uint64_t getP(const uint_t& from) INLINE { return _E::get32(from); }
    static void setP(uint_t& from, uint64_t value) INLINE { _E::set32(from, value); }
};

template <typename _E>
class Pointer64
{
public:
    typedef  uint64_t    uint_t;
    typedef  int64_t     sint_t;
    typedef _E E;

    static uint64_t getP(const uint_t& from) INLINE { return _E::get64(from); }
    static uint64_t setP(uint_t& from, uint64_t value) INLINE { return _E::set64(from, value); }
};

#endif /* ArchAbstractionPointer_h */
