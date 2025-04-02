#include <initializer_list>
#include <string_view>
#include "gamesdk.h"
#include "logger.h"

bool initMethod(il2cpp::Il2CppClass* klass, const char* name, int paramsCount, il2cpp::MethodInfo** info, il2cpp::Il2CppMethodPointer* method) {
	*info = const_cast<il2cpp::MethodInfo *>(il2cpp::il2cpp_class_get_method_from_name(
			klass, name, paramsCount));
	if ((*info) == nullptr){
		LOG("methodInfo '%s (%d)' load failed", name, paramsCount);
		return false;
	} else {
		LOG("methodInfo '%s (%d)' loaded. ptr: %p", name, paramsCount, *info);
	}
	*method = (*info)->methodPointer;
	return true;
}

bool initMethodByArgsName(il2cpp::Il2CppClass* klass, const char* name, const std::initializer_list<std::string_view> &paramsNames, il2cpp::MethodInfo** info, il2cpp::Il2CppMethodPointer* method) {
	void* iter = nullptr;
	for (auto* m = const_cast<il2cpp::MethodInfo *>(il2cpp::il2cpp_class_get_methods(klass, &iter)); m != nullptr;
		 m = const_cast<il2cpp::MethodInfo *>(il2cpp::il2cpp_class_get_methods(klass, &iter))) {
		if (strcmp(m->name, name) == 0 && m->parameters_count == paramsNames.size()) {
			for (int i = 0; i < paramsNames.size(); i++) {
				if (paramsNames.begin()[i] != il2cpp::il2cpp_method_get_param_name(m, i))
					goto wrongMethod;
			}
			*info = m;
			LOG("methodInfo '%s (%d)' loaded by args. ptr: %p", name, paramsNames.size(), m);
			*method = (m)->methodPointer;
			return true;
		}
		wrongMethod:
		; // noop
	}
	LOG("methodInfo '%s (%d)' load by args failed", name, paramsNames.size());
	return false;
}

Game::RegisterGameClass* Game::RegisterGameClass::s_pBase = nullptr;

Game::RegisterGameClassMethodBase::RegisterGameClassMethodBase(RegisterGameClass& registrar, il2cpp::MethodInfo** info,
il2cpp::Il2CppMethodPointer* method) {
	m_pNext = registrar.m_pMethodsBase;
	registrar.m_pMethodsBase = this;
	m_ppinfo = info;
	m_ppmethod = method;
}

Game::RegisterGameClass::RegisterGameClass(const il2cpp::Il2CppAssembly** assembly, const char* namespaze, const char* classname, il2cpp::Il2CppClass** klass) {
	m_pNext = s_pBase;
	s_pBase = this;
	m_ppAssembly = assembly;
	m_pszNamespace = namespaze;
	m_pszClassname = classname;
	m_ppklass = klass;
	m_pMethodsBase = nullptr;
}

bool Game::RegisterGameClass::Init() const {
	if (*m_ppAssembly == nullptr) {
		LOG("class '%s::%s' load failed - no assembly", m_pszNamespace, m_pszClassname);
		return false;
	}
	*m_ppklass = il2cpp::il2cpp_class_from_name((*m_ppAssembly)->image, m_pszNamespace, m_pszClassname);
	if (*m_ppklass == nullptr) {
		LOG("class '%s::%s' load failed", m_pszNamespace, m_pszClassname);
		return false;
	}
	LOG("class '%s::%s' loaded. ptr: %p", m_pszNamespace, m_pszClassname, *m_ppklass);
	bool ok = true;
	for (auto current = m_pMethodsBase; current != nullptr; current = current->m_pNext) {
		ok &= current->Init(*this->m_ppklass);
	}
	return ok;
}

Game::RegisterGameClassMethodArgc::RegisterGameClassMethodArgc(
	RegisterGameClass& registrar,
	il2cpp::MethodInfo** info,
	il2cpp::Il2CppMethodPointer* method,
	const char* methodname,
	int argc
) : RegisterGameClassMethodBase(registrar, info, method) {
	m_pszMethodName = methodname;
	m_iArgc = argc;
}

bool Game::RegisterGameClassMethodArgc::Init(il2cpp::Il2CppClass *klass) {
	*m_ppinfo = const_cast<il2cpp::MethodInfo *>(il2cpp::il2cpp_class_get_method_from_name(
			klass, m_pszMethodName, m_iArgc));
	if ((*m_ppinfo) == nullptr){
		LOG("methodInfo '%s' (argc %d) load failed", m_pszMethodName, m_iArgc);
		return false;
	}
	LOG("methodInfo '%s' (argc %d) loaded. ptr: %p", m_pszMethodName, m_iArgc, *m_ppinfo);
	*m_ppmethod = (*m_ppinfo)->methodPointer;
	return true;
}

Game::RegisterGameClassMethodArgname::RegisterGameClassMethodArgname(
	RegisterGameClass& registrar,
	il2cpp::MethodInfo** info,
	il2cpp::Il2CppMethodPointer* method,
	const char* methodname,
	const std::initializer_list<std::string_view>& argNames
) : RegisterGameClassMethodBase(registrar, info, method), m_pArgNames(argNames) {
	m_pszMethodName = methodname;
}

bool Game::RegisterGameClassMethodArgname::Init(il2cpp::Il2CppClass* klass) {
	void* iter = nullptr;
	for (auto* m = const_cast<il2cpp::MethodInfo*>(il2cpp::il2cpp_class_get_methods(klass, &iter)); m != nullptr;
	     m = const_cast<il2cpp::MethodInfo*>(il2cpp::il2cpp_class_get_methods(klass, &iter))) {
		if (strcmp(m->name, m_pszMethodName) == 0 && m->parameters_count == m_pArgNames.size()) {
			for (int i = 0; i < m_pArgNames.size(); i++) {
				if (m_pArgNames.begin()[i] != il2cpp::il2cpp_method_get_param_name(m, i))
					goto wrongMethod;
			}
			*m_ppinfo = m;
			LOG("methodInfo '%s' (argc %d) loaded by args. ptr: %p", m_pszMethodName, m_pArgNames.size(), m);
			*m_ppmethod = (m)->methodPointer;
			return true;
		}
	wrongMethod:
		; // noop
	}
	LOG("methodInfo '%s' (argc %d) load by args failed", m_pszMethodName, m_pArgNames.size());
	return false;
}

bool Game::Initialize() {
	bool ok = true;
#define GAME_ASSEMBLY_INIT(dllname, cname) \
	cname##Assembly = il2cpp::il2cpp_domain_assembly_open(il2cpp::il2cpp_domain_get(), dllname); \
	if (!cname##Assembly) { \
		LOG("assembly '" dllname "' load failed"); \
		ok = false; \
	}

	GAME_ASSEMBLY_INIT("DissonanceVoip.dll", DissonanceVoip)
	GAME_ASSEMBLY_INIT("UnityEngine.IMGUIModule.dll", UnityEngine_IMGUIModule)
	GAME_ASSEMBLY_INIT("UnityEngine.CoreModule.dll", UnityEngine_CoreModule)
	GAME_ASSEMBLY_INIT("Assembly-CSharp.dll", Assembly_CSharp)
	GAME_ASSEMBLY_INIT("mscorlib.dll", mscorlib)
	GAME_ASSEMBLY_INIT("Heathen.Steamworks.dll", Heathen_Steamworks)
	GAME_ASSEMBLY_INIT("com.rlabrecque.steamworks.net.dll", com_rlabrecque_steamworks_net)

	for (auto current = Game::RegisterGameClass::s_pBase; current != nullptr; current = current->m_pNext) {
		ok &= current->Init();
	}

	// todo: make this not be here
	void* iter = nullptr;
	for (il2cpp::Il2CppClass* c = il2cpp::il2cpp_class_get_nested_types(UnityEngine::GUI::klass, &iter); c != nullptr;
		 c = il2cpp::il2cpp_class_get_nested_types(UnityEngine::GUI::klass, &iter)) {
		if (strcmp(c->name, "WindowFunction") == 0) {
			UnityEngine::GUI::WindowFunction::klass = c;
			goto WindowFunctionFound;
		}
	} // else
	LOG("WindowFunction load failed.");
	ok = false;
	WindowFunctionFound:
	LOG("WindowFunction loaded. ptr: %p", UnityEngine::GUI::WindowFunction::klass);
	return ok;
}
