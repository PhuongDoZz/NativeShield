//
// Created by PhuongDo on 9/4/2025.
//

#ifndef NATIVE_SHIELD_CONSTANTS_H
#define NATIVE_SHIELD_CONSTANTS_H

#define _forceinline __attribute__((always_inline)) inline

#ifdef __LP64__
#define x32_64(_32, _64) _64
#else
#define x32_64(_32, _64) _32
#endif

using Pointer = unsigned long;

constexpr Pointer null = 0UL;

#endif //NATIVE_SHIELD_CONSTANTS_H
