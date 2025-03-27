#pragma once
#include <cstdint>
#include <windows.h>
#include "logger.h"

#define DEFINE_MANAGED_METHOD(ret, convention, funcname, params) \
typedef ret (convention *funcname##_t) params; \
inline funcname##_t funcname;

namespace il2cpp {
#include "UnityHeaders/31-2022.3.33-.h"

#define DO_API(ret, funcname, params) DEFINE_MANAGED_METHOD(ret, __stdcall, funcname, params)

#include "Il2CppAPIHeaders/2021.2.0-2023.1.99.h"

#undef DO_API

	// there is probably a way to make this look less retarded, but idk
	class gchandle {
	public:
		gchandle(bool weakref = false) : m_bWeakref(weakref) {}
		explicit gchandle(il2cpp::Il2CppObject* object, bool weakref) : m_bWeakref(weakref) {
			Set(object);
		}
		~gchandle() {
			if (m_bHasHandle)
				il2cpp_gchandle_free(m_handle);
		}
		void Set(il2cpp::Il2CppObject* object) {
			if (m_bHasHandle)
				il2cpp_gchandle_free(m_handle);
			if (object) {
				if (m_bWeakref)
					m_handle = il2cpp_gchandle_new_weakref(object, false);
				else
					m_handle = il2cpp_gchandle_new(object, false);
				m_bHasHandle = true;
			} else {
				m_bHasHandle = false;
			}
		}
		il2cpp::Il2CppObject* Get() const {
			if (m_bHasHandle)
				return il2cpp_gchandle_get_target(m_handle);
			return nullptr;
		}
		gchandle& operator=(il2cpp::Il2CppObject* object)
		{
			Set(object);
			return *this;
		}
		// yeah, piss off clion, that's the whole point.
		operator il2cpp::Il2CppObject*() const { // NOLINT(*-explicit-constructor)
			return Get();
		}
		uint32_t m_handle;
		bool m_bHasHandle = false;
		bool m_bWeakref = false;
	};
	inline Il2CppObject* ClassGetTypeObject(Il2CppClass* klass) {
		return il2cpp_type_get_object(il2cpp_class_get_type(klass));
	}
}

void LoadIl2CppAddress(FARPROC handle, LPCSTR lpProcName);

inline il2cpp::Il2CppString* operator "" _il2cpp(const char* str, size_t len)
{
	return il2cpp::il2cpp_string_new_len(str, len);
}

//#define DEFINE_IL2CPP_FUNC(ret, funcname, ...) \
//typedef ret (__stdcall* funcname##_t)(__VA_ARGS__); \
//funcname##_t funcname##_orig;
//
//DEFINE_IL2CPP_FUNC(int, il2cpp_init, const char *domain_name)
//DEFINE_IL2CPP_FUNC(void*, il2cpp_class_from_name, void* image, const char* namespacee, const char* name)
//DEFINE_IL2CPP_FUNC(void*, il2cpp_class_get_method_from_name, void* classs, const char* name, DWORD param_count)
//DEFINE_IL2CPP_FUNC(void*, il2cpp_runtime_invoke, void* method, void* instance, void* *params, void* exc)
//DEFINE_IL2CPP_FUNC(void*, il2cpp_thread_attach, void* domain)
//DEFINE_IL2CPP_FUNC(void*, il2cpp_get_root_domain)
//DEFINE_IL2CPP_FUNC(const char*, il2cpp_method_get_name, void* method)
