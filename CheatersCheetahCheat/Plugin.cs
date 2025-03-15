using BepInEx;
using BepInEx.Unity.IL2CPP;
using CheatersCheetahCheat.cheats;
using DataStructs;
using Game.Player.CharacterController;
using HarmonyLib;
using HeathenEngineering.SteamworksIntegration;
using Il2CppInterop.Runtime.Injection;
using UImGui;
using UnityEngine;
using VoiceChat;
using Object = UnityEngine.Object;

namespace CheatersCheetahCheat;

[BepInPlugin("ru.acuifex.CheatersCheetahCheat", "", "1.0.0")]
public class Plugin : BasePlugin
{
    		        
    public static BepInEx.Logging.ManualLogSource log;
    public static Harmony harmony;
    public static GameObject cheatObject;
    public Plugin()
    {
        log = Log;
    }
    
    public void Hook(Type obj, Type hooker, string methodName, bool prefix = false)
    {
        var originalMethod = AccessTools.Method(obj, methodName);
        Log.LogMessage("[Trainer] Harmony - Original Method: " + originalMethod.DeclaringType.Name + "." + originalMethod.Name);
        var postMethod = AccessTools.Method(hooker, methodName);
        Log.LogMessage("[Trainer] Harmony - Postfix Method: " + postMethod.DeclaringType.Name + "." + postMethod.Name);
        if (prefix)
        {
            harmony.Patch(originalMethod, prefix: new HarmonyMethod(postMethod));
            Log.LogMessage("[Trainer] Harmony - Runtime Prefix Hook Applied");
        }
        else
        {
            harmony.Patch(originalMethod, postfix: new HarmonyMethod(postMethod));
            Log.LogMessage("[Trainer] Harmony - Runtime Hook Applied");
        }
    }
    
    public override void Load()
    {
        // Plugin startup logic
        Log.LogInfo("Plugin Example.Plugin is loaded2!");
        // ImguiManager.ToggleMenu(false, false);
        Log.LogMessage("[Trainer] Registering TrainerComponent in Il2Cpp");

        try
        {
            // Register our custom Types in Il2Cpp
            if (!ClassInjector.IsTypeRegisteredInIl2Cpp<CheatObject>())
                ClassInjector.RegisterTypeInIl2Cpp<CheatObject>();
            
            cheatObject = new GameObject("CheatObject");
            // took those two lines from bepinex's Il2CppUtils.AddComponent.
            // no idea why this works. no callbacks if i dont do this.
            cheatObject.hideFlags = HideFlags.HideAndDontSave;
            cheatObject.AddComponent(Il2CppInterop.Runtime.Il2CppType.From(typeof(CheatObject)));
            // Object.DontDestroyOnLoad(cheatObject);
            // var ret = IL2CPPChainloader.AddUnityComponent<CheatObject>();
        }
        catch (Exception ex)
        {
            Log.LogError("[Trainer] FAILED to Register Il2Cpp Type: TrainerComponent!" + ex.ToString());
        }
	
        try
        {
            harmony = new Harmony("ru.acuifex.CheatersCheetahCheat");
            
            Log.LogMessage($"[Trainer] created harmony!");
			// Our Primary Unity Event Hooks 
			
            // Hook(typeof(RenderTextureManager), typeof(CheatObject), "Update");
            // Hook(typeof(PlayerInstance), typeof(CheatObject), "Start");
            Hook(typeof(PlayerWeaponController), typeof(Nospread), "SpreadAppliedAngle", true);
            Hook(typeof(CheatModeExtensions), typeof(BypassLegit), "IsFeatureEnabled");
            Hook(typeof(VoiceChatManager), typeof(VoiceHold), "UpdateBroadcastMode", true);
            Hook(typeof(TextChatManager), typeof(ChatOverlay), "AddMessage");
            Hook(typeof(LobbyManager), typeof(BypassLobbySize), "Create", true);
            // currently crashes. probably due to a bug in MonoMod. hopefully not threading related.
            // Hook(typeof(Ragebot), typeof(ShouldApplyRagebotHook), "ShouldApplyRagebot", false);
        }
        catch (Exception e)
        {
            log.LogError("[Trainer] Harmony - FAILED to Apply Patch's:" + e);
        }

        // AddComponent<Test>();
        // AddComponent<UImGui.UImGui>();
        // AddComponent<ShowDemoWindow>();
    }

    public override bool Unload()
    {
        Log.LogMessage("[Trainer] Unloading Plugin!");
        harmony.UnpatchSelf();
        Object.DestroyImmediate(cheatObject);
        return false;
    }
}