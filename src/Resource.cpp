// Copyright 2021-2026 Stefan Zellmann
// SPDX-License-Identifier: Apache-2.0

#include <unordered_map>

#include "Resource.h"

namespace fake
{
    static std::unordered_map<ResourceHandle, ManagedResource> managedResourceMap;

    ResourceHandle RegisterManagedResource(ManagedResource resource)
    {
        static ResourceHandle nextHandle = 0;

        ResourceHandle thisHandle = nextHandle++;

        managedResourceMap.insert({ thisHandle, resource });

        return thisHandle;
    }

    void UnregisterManagedResource(ResourceHandle handle)
    {
        managedResourceMap.erase(handle);
    }

    ManagedResource GetManagedResource(ResourceHandle handle)
    {
        auto it = managedResourceMap.find(handle);

        if (it == managedResourceMap.end())
            return nullptr;
        else
            return it->second;
    }


    ContextResource::ContextResource()
    {
    }

    ContextResource::~ContextResource()
    {
    }

    Context* ContextResource::getContext() const
    {
        return context;
    }

    void ContextResource::setContext(Context* ctx)
    {
        context = ctx;
    }

} // fake
