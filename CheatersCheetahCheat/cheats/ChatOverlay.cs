using DataStructs;
using HarmonyLib;
using Unity.Mathematics;
using UnityEngine;

namespace CheatersCheetahCheat.cheats;

public class ChatOverlay : ICheat
{
    public static bool Enabled = false;
    public static List<TextChatMessage> Messages = new List<TextChatMessage>();
    public static int MaxMessages = 20;
    private static Texture2D texture = new Texture2D(1, 1);
    private static GUIStyle gs = new GUIStyle();

    static ChatOverlay()
    {
        texture.SetPixel(0, 0, GUI.backgroundColor);
        texture.Apply();
        gs.normal.background = Texture2D.grayTexture;
    }
    
    [HarmonyPostfix]
    public static void AddMessage(TextChatMessage message)
    {
        Messages.Add(message);
        while (Messages.Count > MaxMessages)
        {
            Messages.RemoveAt(0);
        }
        Plugin.log.LogMessage($"[Trainer] MESSAGE: [{message.senderName}]: {message.message}");
    }

    public void OnGui()
    {
        if (!Enabled)
            return;
        GUILayout.BeginArea(new Rect(50, Screen.height - 250, 600, 200), gs);
        
        for (int i = math.min(Messages.Count, MaxMessages)-1; i >= 0; i--)
        {
            GUILayout.Label($"[{Messages[i].senderName}]: {Messages[i].message}");
        }
        GUILayout.EndArea();
    }
}