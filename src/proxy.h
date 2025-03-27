#pragma once

#include <cstdio>
#include "logger.h"


#define DLL_POSTFIX TEXT(".dll")

extern void load_functions(void *dll);

static inline void load_proxy(const char *module_name) {
	size_t module_name_len = strlen(module_name);


	UINT sys_len = GetSystemDirectory(NULL, 0);
	char sys_full_path[4096];
	GetSystemDirectory(sys_full_path, sys_len);
	sys_full_path[sys_len - 1] = TEXT('\\');
	strcpy(strcpy(sys_full_path + sys_len, module_name) + module_name_len,
		   DLL_POSTFIX);

	LOG("Looking for original DLL from %s", sys_full_path);

	void *handle = LoadLibrary(sys_full_path);

	if (handle == nullptr) {
		LOG("Unable to load original %s.dll!", module_name);
		return;
	}

	load_functions(handle);
}