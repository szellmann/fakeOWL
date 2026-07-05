// Copyright 2021-2026 Stefan Zellmann
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string.h>

__device__
inline float __int_as_float(int i)
{
    float f;
    memcpy(&f, &i, sizeof(f));
    return f;
}

__device__
inline double __longlong_as_double(long long ll)
{
    double d;
    memcpy(&d, &ll, sizeof(d));
    return d;
}


