/* SPDX-License-Identifier: MIT */

#include "globals.h"
#include "home.h"
#include "error.h"

/* NOTE: this should be compile time */
struct Screen screens[] = {
    {
        "home",
        NULL,
        draw_home
    },
    {
        "error",
        NULL,
        draw_error
    }
};
