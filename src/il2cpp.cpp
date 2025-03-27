//
// Created by acuifex on 25/03/2025.
//
#include "il2cpp.h"

void LoadIl2CppAddress(FARPROC handle, LPCSTR lpProcName) {
#define DO_API(ret, name, params) \
    if (lstrcmpA(lpProcName, #name) == 0) { \
        LOG("il2cpp loading " #name " at %p", handle); \
        il2cpp::name = (il2cpp::name##_t)handle; \
    }

#include "Il2CppAPIHeaders/2021.2.0-2023.1.99.h"

#undef DO_API
}

