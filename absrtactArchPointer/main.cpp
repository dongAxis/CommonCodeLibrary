//
//  main.c
//  absrtactArchPointer
//
//  Created by Axis on 2/23/16.
//  Copyright © 2016 Axis. All rights reserved.
//

#include <iostream>
#include "ArchAbstractionPointer.h"

template <typename P>
struct test_class {};

template<> struct test_class<Pointer32<BigEndian>> { const char* type = "32 pointer under big endian"; };
template<> struct test_class<Pointer32<LittleEndian>> {const char* type = "32 pointer under little endian"; };
template<> struct test_class<Pointer64<BigEndian>> { const char* type = "64 pointer under big endian"; };
template<> struct test_class<Pointer64<LittleEndian>> { const char* type = "64 pointer under little endian"; };

struct ppc
{
    typedef Pointer32<BigEndian> P;
};

struct ppc64
{
    typedef Pointer64<BigEndian> P;
};

struct x86
{
    typedef Pointer32<LittleEndian> P;
};

struct x64
{
    typedef Pointer64<LittleEndian> P;
};

template<typename T>
struct test_trail
{
private:
    typedef typename T::P P;
    typedef typename T::P::E E;
    typedef typename T::P::uint_t puint_t;
};

int main(int argc, const char * argv[])
{
    test_class<x64::P> test;
    std::cout << test.type << std::endl;

    test_class<ppc::P> test2;
    std::cout << test2.type << std::endl;
}
