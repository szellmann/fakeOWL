// Copyright 2021-2026 Stefan Zellmann
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <cstdint>

namespace fake
{
    // Managed resource

    typedef uint32_t ResourceHandle;
    typedef struct
    {
        ResourceHandle resourceHandle;
    } ManagedResource_;
    typedef ManagedResource_* ManagedResource;

    ResourceHandle RegisterManagedResource(ManagedResource resource);

    void UnregisterManagedResource(ResourceHandle handle);

    ManagedResource GetManagedResource(ResourceHandle handle);


    // Context resource

    class Context;

    class ContextResource : public ManagedResource_
    {
    public:
        ContextResource();
        virtual ~ContextResource();

        Context* getContext() const;
        virtual void setContext(Context* ctx);
    protected:
        Context* context;
    };

} // fake
