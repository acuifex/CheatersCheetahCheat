using Dissonance;
using HarmonyLib;
using UnityEngine;
using UnityEngine.InputSystem;
using VoiceChat;

namespace CheatersCheetahCheat.cheats;

public class VoiceHold : ICheat
{
    public static bool Enabled = false;
    public static bool WasEnabled = false;
    
    [HarmonyPrefix]
    public static bool UpdateBroadcastMode()
    {
        // Plugin.log.LogMessage("[Trainer] UpdateBroadcastMode:" + Enabled);
        if (Enabled)
        {
            OverrideIsPressed(true);
            return false;
        }

        if (WasEnabled && !Enabled)
        {
            OverrideIsPressed(false);
        }
        WasEnabled = Enabled;
        return true;
    }

    private static bool logged_error = false;
    private static float lastTimeLoggedState;
    
    public static void OverrideIsPressed(bool value)
    {
        var globalVoiceBroadcastTrigger = VoiceChatManager._instance.globalVoiceBroadcastTrigger;
        var groupVoiceBroadcastTrigger = VoiceChatManager._instance.groupVoiceBroadcastTrigger;
        if (globalVoiceBroadcastTrigger == null && groupVoiceBroadcastTrigger == null)
        {
            if (!logged_error)
            {
                Plugin.log.LogMessage("[Trainer] VoiceHold failed to find both broadcast triggers");
                logged_error = true;
            }
        }
        else
        {
            logged_error = false;
        }
        if (globalVoiceBroadcastTrigger != null)
            globalVoiceBroadcastTrigger._mode = value ? CommActivationMode.Open : CommActivationMode.None;
        if (groupVoiceBroadcastTrigger != null)
            groupVoiceBroadcastTrigger._mode = value ? CommActivationMode.Open : CommActivationMode.None;

        if (lastTimeLoggedState < Time.time - 5)
        {
            lastTimeLoggedState = Time.time;
            Plugin.log.LogMessage($"[Trainer] broadcast status: global:{globalVoiceBroadcastTrigger?.IsTransmitting}" +
                                  $" group:{groupVoiceBroadcastTrigger?.IsTransmitting}");
        }

        VoiceChatManager.OnPlayerSpeakingStateChanged?.Invoke(PlayerInstance.LocalInstance, value, value);
    }
    public void Update()
    {
        if (Keyboard.current.numpad5Key.wasPressedThisFrame)
        {
            Enabled = !Enabled;
            Plugin.log.LogMessage("[Trainer] toggling VoiceHold:" + Enabled);
            
        }
    }
}