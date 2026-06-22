// Copyright 2021-2026 Stefan Zellmann
// SPDX-License-Identifier: Apache-2.0

#include <cstring>

#include "DataType.h"
#include "Logging.h"
#include "Params.h"

namespace fake
{
    Params::Params(std::size_t sizeOfVarStruct, const OWLVarDecl* vars, int numVars)
        : VarDecl(sizeOfVarStruct, vars, numVars)
    {
    }

} // fake
