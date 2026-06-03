// Copyright (c) 2023-2026 Christiaan (chris@boreddev.nl)
// This software is released under the GNU General Public License v3.0. See LICENSE file for details.
// This header needs to maintain in any file it is present in, as per the GPL license terms.
#ifndef _STDINT_H
#define _STDINT_H
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long int64_t;
typedef unsigned long uint64_t;

typedef __UINT_LEAST64_TYPE__ uint_least64_t;
typedef __INT_LEAST64_TYPE__ int_least64_t;
typedef __INT_FAST64_TYPE__ int_fast64_t;
typedef __UINT_FAST64_TYPE__ uint_fast64_t;
typedef __UINT_LEAST32_TYPE__ uint_least32_t;
typedef __INT_LEAST32_TYPE__ int_least32_t;
typedef __INT_FAST32_TYPE__ int_fast32_t;
typedef __UINT_FAST32_TYPE__ uint_fast32_t;
typedef __UINT_LEAST16_TYPE__ uint_least16_t;
typedef __INT_LEAST16_TYPE__ int_least16_t;
typedef __INT_FAST16_TYPE__ int_fast16_t;
typedef __UINT_FAST16_TYPE__ uint_fast16_t;
typedef __UINT_LEAST8_TYPE__ uint_least8_t;
typedef __INT_LEAST8_TYPE__ int_least8_t;
typedef __INT_FAST8_TYPE__ int_fast8_t;
typedef __UINT_FAST8_TYPE__ uint_fast8_t;

#ifdef __INTMAX_TYPE__
typedef __INTMAX_TYPE__ intmax_t;
typedef __UINTMAX_TYPE__ uintmax_t;
#else
#if defined(__x86_64__) || defined(__aarch64__) || defined(_M_X64)
typedef long long intmax_t;
typedef unsigned long long uintmax_t;
#else
typedef long intmax_t;
typedef unsigned long uintmax_t;
#endif
#endif

#ifndef _INTPTR_T
#define _INTPTR_T
typedef long intptr_t;
#endif

#ifndef _UINTPTR_T
#define _UINTPTR_T
typedef unsigned long uintptr_t;
#endif

#endif
