// Copyright 2021-2026 Stefan Zellmann
// SPDX-License-Identifier: Apache-2.0

#include "Miss.h"

namespace fake
{
    Miss::Miss(std::size_t sizeOfVarStruct, const OWLVarDecl* vars, int numVars)
        : VarDecl(sizeOfVarStruct, vars, numVars)
    {
    }

    std::string Miss::entryPointPrefix()
    {
        return "__miss__";
    }
} // fake
