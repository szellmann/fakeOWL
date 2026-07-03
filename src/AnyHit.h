// Copyright 2021-2026 Stefan Zellmann
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Program.h"

namespace fake
{
    struct AnyHit : Program
    {
        std::string entryPointPrefix();

        int rayType = 0;

        // Symbol to prepare an intersection program call
        void* fakePrepareAnyHitSym = nullptr;

    };
} // fake
