// Copyright (c) 2023-2026 Christiaan (chris@boreddev.nl)
// This software is released under the GNU General Public License v3.0. See LICENSE file for details.
// This header needs to maintain in any file it is present in, as per the GPL license terms.
#include "locale.h"
#include "string.h"

static struct lconv _b_lconv = {
    ".", "", "", "", "", ".", "", "", "", "",
    0, 0, 0, 0, 0, 0, 0, 0
};

__attribute__((weak)) char *setlocale(int category, const char *locale) {
    (void)category;
    if (locale == NULL || strcmp(locale, "C") == 0 || strcmp(locale, "") == 0) {
        return "C";
    }
    return NULL;
}

__attribute__((weak)) struct lconv *localeconv(void) {
    return &_b_lconv;
}
