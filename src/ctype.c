// Copyright (c) 2023-2026 Christiaan (chris@boreddev.nl)
// This software is released under the GNU General Public License v3.0. See LICENSE file for details.
// This header needs to maintain in any file it is present in, as per the GPL license terms.
#include "ctype.h"

__attribute__((weak)) int isdigit(int c) { return (c >= '0' && c <= '9'); }
__attribute__((weak)) int isalpha(int c) { return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')); }
__attribute__((weak)) int isalnum(int c) { return isalpha(c) || isdigit(c); }
__attribute__((weak)) int isspace(int c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
}
__attribute__((weak)) int isupper(int c) { return (c >= 'A' && c <= 'Z'); }
__attribute__((weak)) int islower(int c) { return (c >= 'a' && c <= 'z'); }
__attribute__((weak)) int isxdigit(int c) {
    return isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}
__attribute__((weak)) int iscntrl(int c) { return ((c >= 0 && c < 32) || c == 127); }
__attribute__((weak)) int isprint(int c) { return (c >= 32 && c < 127); }
__attribute__((weak)) int isgraph(int c) { return (c > 32 && c < 127); }
__attribute__((weak)) int ispunct(int c) {
    return isprint(c) && !isalnum(c) && !isspace(c);
}
__attribute__((weak)) int tolower(int c) { return isupper(c) ? (c - 'A' + 'a') : c; }
__attribute__((weak)) int toupper(int c) { return islower(c) ? (c - 'a' + 'A') : c; }
