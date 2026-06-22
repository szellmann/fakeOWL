// Copyright 2021-2026 Stefan Zellmann
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <cstdint>

#include <owl/owl_host.h>

#include "Resource.h"
#include "VarDecl.h"

namespace fake
{
    struct Params : ContextResource, VarDecl
    {
        Params(std::size_t sizeOfVarStruct, const OWLVarDecl* vars, int numVars);
    };

} // fake
