using HarmonyLib;

namespace CheatersCheetahCheat.cheats;

public class BypassLobbySize : ICheat
{
    public static bool Enabled = false;
    
    public static int Slots = 32;

    [HarmonyPrefix]
    public static void Create(HeathenEngineering.SteamworksIntegration.LobbyManager __instance)
    {
        if (Enabled)
        {
            Plugin.log.LogMessage($"[Trainer] Lobby size bypassed: {__instance.createArguments.slots} -> {Slots}");
            __instance.createArguments.slots = Slots;
        }
    }
}