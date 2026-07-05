// Copyright 2021-2026 Stefan Zellmann
// SPDX-License-Identifier: Apache-2.0

#pragma once

#define NOMINMAX
#include <windows.h>

#define RTLD_LAZY    -1
#define RTLD_NOW     -1

inline void *dlopen(const char *fn, int flags)
{ return (void *)LoadLibraryA(fn); }

inline void *dlsym(void *handle, const char *sym)
{ return (void *)GetProcAddress((HMODULE)handle, sym); }

inline int dlclose(void *handle)
{ return FreeLibrary((HMODULE)handle) ? 0 : -1; }

inline const char *dlerror()
{ return "Unsspecified dynamic link error"; }
