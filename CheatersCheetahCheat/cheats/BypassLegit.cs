using DataStructs;
using HarmonyLib;
using UnityEngine.InputSystem;

namespace CheatersCheetahCheat.cheats;

public class BypassLegit : ICheat
{
    public static bool Enabled = false;
    
    [HarmonyPostfix]
    public static void IsFeatureEnabled(ref bool __result, CheatMode current, CheatMode cheatMode) 
    {
        if (Enabled)
            __result = true;
    }
    public void Update()
    {
        if (Keyboard.current.numpad3Key.wasPressedThisFrame)
        {
            Enabled = !Enabled;
            Plugin.log.LogMessage("[Trainer] toggling legit bypass:" + Enabled);
        }
    }
}