#pragma once

#include "il2cpp.h"
#include <initializer_list>
#include <string_view>
#include <vector>

#define DEFINE_GAME_CLASS inline il2cpp::Il2CppClass* klass;
#define DEFINE_GAME_CLASS_METHOD(ret, funcname, params) \
DEFINE_MANAGED_METHOD(ret, __fastcall, funcname, params); \
inline il2cpp::MethodInfo* funcname##_info;
#define DEFINE_GAME_ASSEMBLY(name) inline const il2cpp::Il2CppAssembly* name##Assembly

#define REGISTER_GAME_CLASS(assembly, managednamespace, classname) DEFINE_GAME_CLASS \
inline RegisterGameClass klassRegistrator(&assembly##Assembly, managednamespace, #classname, &klass);

#define REGISTER_GAME_CLASS_METHOD(ret, funcname, params, argc) DEFINE_GAME_CLASS_METHOD(ret, funcname, params) \
inline RegisterGameClassMethodArgc funcname##Registrator(klassRegistrator, &funcname##_info, (il2cpp::Il2CppMethodPointer*)&funcname, #funcname, argc)

#define REGISTER_GAME_CLASS_METHOD_ARGNAME(ret, funcname, params, argnames) DEFINE_GAME_CLASS_METHOD(ret, funcname, params) \
inline RegisterGameClassMethodArgname funcname##Registrator(klassRegistrator, &funcname##_info, (il2cpp::Il2CppMethodPointer*)&funcname, #funcname, argnames)

// TODO: using generated types & methods would've been nice, but clion fucking chokes on 30+ mib of generated code.
// manually take what we need for now.
// technically they all should have method parameter at the end, but ehhh. i think that's only used in a generic.
namespace Game {
	class RegisterGameClass;

	class RegisterGameClassMethodBase {
	public:
		RegisterGameClassMethodBase* m_pNext;
		il2cpp::MethodInfo** m_ppinfo;
		il2cpp::Il2CppMethodPointer* m_ppmethod;
		virtual ~RegisterGameClassMethodBase() = default;

		RegisterGameClassMethodBase(RegisterGameClass& registrar, il2cpp::MethodInfo** info, il2cpp::Il2CppMethodPointer* method);
		virtual bool Init(il2cpp::Il2CppClass* klass) = 0;
	};

	class RegisterGameClass {
	public:
		static RegisterGameClass* s_pBase;
		RegisterGameClass* m_pNext;
		const il2cpp::Il2CppAssembly** m_ppAssembly;
		const char* m_pszNamespace;
		const char* m_pszClassname;
		il2cpp::Il2CppClass** m_ppklass;

		RegisterGameClassMethodBase* m_pMethodsBase;

		RegisterGameClass(const il2cpp::Il2CppAssembly** assembly, const char* namespaze, const char* classname, il2cpp::Il2CppClass** klass);
		bool Init() const;
	};

	class RegisterGameClassMethodArgc : RegisterGameClassMethodBase {
		const char* m_pszMethodName;
		int m_iArgc;
	public:
		RegisterGameClassMethodArgc(RegisterGameClass& registrar, il2cpp::MethodInfo** info, il2cpp::Il2CppMethodPointer* method, const char* methodname, int argc);
		bool Init(il2cpp::Il2CppClass* klass) override;
	};

	class RegisterGameClassMethodArgname : RegisterGameClassMethodBase {
		const char* m_pszMethodName;
		// kinda wanted to store initializer_list reference, but i think it's allocated on stack only.
		const std::vector<std::string_view> m_pArgNames;
	public:
		RegisterGameClassMethodArgname(RegisterGameClass& registrar, il2cpp::MethodInfo** info, il2cpp::Il2CppMethodPointer* method, const char* methodname, const std::initializer_list<std::string_view>& argNames);
		bool Init(il2cpp::Il2CppClass* klass) override;
	};

	DEFINE_GAME_ASSEMBLY(DissonanceVoip);
	DEFINE_GAME_ASSEMBLY(UnityEngine_IMGUIModule);
	DEFINE_GAME_ASSEMBLY(UnityEngine_CoreModule);
	DEFINE_GAME_ASSEMBLY(Assembly_CSharp);
	DEFINE_GAME_ASSEMBLY(mscorlib);
	DEFINE_GAME_ASSEMBLY(Heathen_Steamworks);
	DEFINE_GAME_ASSEMBLY(com_rlabrecque_steamworks_net);
	namespace UnityEngine {
		struct Rect_Fields {
			float m_XMin;
			float m_YMin;
			float m_Width;
			float m_Height;
		};
		// actually a struct with 1 member.
		typedef Rect_Fields Rect_o;
		namespace GUI {
			namespace WindowFunction {
				DEFINE_GAME_CLASS;
			}
			REGISTER_GAME_CLASS(UnityEngine_IMGUIModule, "UnityEngine", GUI);
			REGISTER_GAME_CLASS_METHOD(void, Label, (Rect_o* position, il2cpp::Il2CppString* text), 2);
			REGISTER_GAME_CLASS_METHOD(void, DragWindow, (Rect_o* position), 1);
		}
		namespace GUILayout {
			REGISTER_GAME_CLASS(UnityEngine_IMGUIModule, "UnityEngine", GUILayout);
			REGISTER_GAME_CLASS_METHOD(Rect_o*, Window, (Rect_o* return_storage_, int32_t id, Rect_o* clientRect, il2cpp::Il2CppObject* func, il2cpp::Il2CppString* title, il2cpp::Il2CppArray* options), 5);
			REGISTER_GAME_CLASS_METHOD(void, Label, (il2cpp::Il2CppString* text, il2cpp::Il2CppArray* options), 2);
			REGISTER_GAME_CLASS_METHOD(bool, Toggle, (bool value, il2cpp::Il2CppString* text, il2cpp::Il2CppArray* options), 3);
			REGISTER_GAME_CLASS_METHOD(bool, Button, (il2cpp::Il2CppString* text, il2cpp::Il2CppArray* options), 2);
			REGISTER_GAME_CLASS_METHOD(float, HorizontalSlider, (float value, float leftValue, float rightValue, il2cpp::Il2CppArray* options), 4);
			REGISTER_GAME_CLASS_METHOD(void, BeginHorizontal, (il2cpp::Il2CppArray* options), 1);
			REGISTER_GAME_CLASS_METHOD(void, EndHorizontal, (), 0);
			REGISTER_GAME_CLASS_METHOD(void, BeginArea, (Rect_o* screenRect), 1);
			REGISTER_GAME_CLASS_METHOD(void, EndArea, (), 0);
		}
		namespace GUILayoutOption {
			REGISTER_GAME_CLASS(UnityEngine_IMGUIModule, "UnityEngine", GUILayoutOption);
		}
		namespace GameObject {
			REGISTER_GAME_CLASS(UnityEngine_CoreModule, "UnityEngine", GameObject);
			REGISTER_GAME_CLASS_METHOD(il2cpp::Il2CppObject*, Find, (il2cpp::Il2CppString* name), 1);
			REGISTER_GAME_CLASS_METHOD(il2cpp::Il2CppObject*, AddComponent, (il2cpp::Il2CppObject* this_, il2cpp::Il2CppObject* type), 1);
			REGISTER_GAME_CLASS_METHOD(il2cpp::Il2CppObject*, FindObjectOfType, (il2cpp::Il2CppObject* type, bool includeInactive), 2);
		}
		namespace Object {
			REGISTER_GAME_CLASS(UnityEngine_CoreModule, "UnityEngine", Object);
			// you MUST check op_Implicit or m_CachedPtr or IsNativeObjectAlive,
			// because the object is not guaranteed to get collected.
			// op_Implicit has a nullptr check for exists
			REGISTER_GAME_CLASS_METHOD(bool, op_Implicit, (il2cpp::Il2CppObject* exists), 1);
		}
		namespace Time {
			REGISTER_GAME_CLASS(UnityEngine_CoreModule, "UnityEngine", Time);
			REGISTER_GAME_CLASS_METHOD(float, get_time, (), 0);
		}
	}
	namespace Dissonance::Demo::Logo {
		REGISTER_GAME_CLASS(DissonanceVoip, "Dissonance.Demo", Logo);
		REGISTER_GAME_CLASS_METHOD(void, OnGUI, (il2cpp::Il2CppObject* this_), 0);
	}
	namespace Dissonance::VoiceBroadcastTrigger {
		REGISTER_GAME_CLASS(DissonanceVoip, "Dissonance", VoiceBroadcastTrigger);
		REGISTER_GAME_CLASS_METHOD(void, set_Mode, (il2cpp::Il2CppObject* this_, int32_t value), 1);
		REGISTER_GAME_CLASS_METHOD(bool, get_IsTransmitting, (il2cpp::Il2CppObject* this_), 0);
	}
	namespace SkateMenu::ImguiManager {
		REGISTER_GAME_CLASS(Assembly_CSharp, "SkateMenu", ImguiManager);
		REGISTER_GAME_CLASS_METHOD(void, Update, (il2cpp::Il2CppObject* this_), 0);
		REGISTER_GAME_CLASS_METHOD(bool, get_IsBaseWindowOpen, (), 0);
	}
	namespace System::Runtime::InteropServices::Marshal {
		REGISTER_GAME_CLASS(mscorlib, "System.Runtime.InteropServices", Marshal);
		REGISTER_GAME_CLASS_METHOD(il2cpp::Il2CppObject*, GetDelegateForFunctionPointer, (uintptr_t ptr, il2cpp::Il2CppObject* t), 2);
	}
	namespace GlobalUI::TextChatComponent {
		REGISTER_GAME_CLASS(Assembly_CSharp, "GlobalUI", TextChatComponent);
		REGISTER_GAME_CLASS_METHOD(void, OnMessageSubmit, (il2cpp::Il2CppObject* this_, il2cpp::Il2CppString* message), 1);
		REGISTER_GAME_CLASS_METHOD_ARGNAME(void, ToggleChatMode, (il2cpp::Il2CppObject* this_, bool allChat), {"allChat"});
	}
	namespace DataStructs::CheatModeExtensions {
		REGISTER_GAME_CLASS(Assembly_CSharp, "DataStructs", CheatModeExtensions);
		REGISTER_GAME_CLASS_METHOD(bool, IsFeatureEnabled, (uint8_t current, uint8_t cheatMode), 2);
	}
	// underscore to avoid ambiguous symbol errors.
	namespace Game_::Player::Aimbot::Ragebot {
		REGISTER_GAME_CLASS(Assembly_CSharp, "Game.Player.Aimbot", Ragebot);
		REGISTER_GAME_CLASS_METHOD(void*, ApplyRagebot,
		                           (void* return_storage_, void* moveData, bool willGetConsumed,
			                           bool willGetConsumedIfPrimaryDown, bool* overwritePrimaryDown), 4);
		REGISTER_GAME_CLASS_METHOD(bool, ShouldActivateAimLock,
		                           (void* aimPoints, int32_t* aimPointIndex,
			                           il2cpp::Il2CppObject* config, bool manual), 4);
		REGISTER_GAME_CLASS_METHOD(void, QueueHitChanceCalculation,
		                           (void* origin, void* aimPoints, int32_t minDamage, float spreadAngle, uint8_t power),
		                           5);
		REGISTER_GAME_CLASS_METHOD(int32_t, GetMinDamageThreshold, (void* aimbot, bool manual), 2);
	}
	namespace Steamworks::AppId_t {
		REGISTER_GAME_CLASS(com_rlabrecque_steamworks_net, "Steamworks", AppId_t);
		REGISTER_GAME_CLASS_METHOD(bool, op_Inequality, (uint32_t x, uint32_t y), 2);
	}
	namespace DataStructs {
		struct SerializableTextChatMessage_Fields {
			il2cpp::Il2CppObject* sender;
			il2cpp::Il2CppString* message;
			uint8_t type;
		};
		// actually a struct with 1 member.
		typedef SerializableTextChatMessage_Fields SerializableTextChatMessage_o;
		namespace TextChatMessageSerializer {
			REGISTER_GAME_CLASS(Assembly_CSharp, "DataStructs", TextChatMessageSerializer);
			REGISTER_GAME_CLASS_METHOD(void, WriteTextChatMessage, (void* writer, SerializableTextChatMessage_o* textChatMessage), 2);
		}
	}
	namespace PlayerInstance {
		REGISTER_GAME_CLASS(Assembly_CSharp, "", PlayerInstance);
		REGISTER_GAME_CLASS_METHOD(il2cpp::Il2CppObject*, get_LocalInstance, (), 0);
		REGISTER_GAME_CLASS_METHOD(void, CmdSendChatToServer, (il2cpp::Il2CppObject* this_, DataStructs::SerializableTextChatMessage_o* message), 1);
	}
	namespace Game_::Player::GamePlayerClient {
		REGISTER_GAME_CLASS(Assembly_CSharp, "Game.Player", GamePlayerClient);
		REGISTER_GAME_CLASS_METHOD(void, CmdSendForceRoundEndRequestToServer, (il2cpp::Il2CppObject* this_), 0);
		REGISTER_GAME_CLASS_METHOD(void, CmdSendLoadoutUpdateRequestToServer, (il2cpp::Il2CppObject* this_, int32_t loadoutIndex, bool ignoreGamePhase), 2);
	}
	namespace VoiceChat
	{
		struct VoiceChatManager_Fields {
			// writing offsets manually smh.
			const char skip[0x18];
			// Dissonance_VoiceBroadcastTrigger_o
			il2cpp::Il2CppObject* groupVoiceBroadcastTrigger;
			il2cpp::Il2CppObject* globalVoiceBroadcastTrigger;
		};
		struct VoiceChatManager_o : il2cpp::Il2CppObject {
			VoiceChatManager_Fields fields;
		};
		namespace VoiceChatManager {
			REGISTER_GAME_CLASS(Assembly_CSharp, "VoiceChat", VoiceChatManager);
			REGISTER_GAME_CLASS_METHOD(void, UpdateBroadcastMode, (VoiceChatManager_o* this_), 0);
		}
	}
	bool Initialize();
}