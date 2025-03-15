using SkateMenu;
using UnityEngine;

namespace CheatersCheetahCheat.cheats;

public class Menu : ICheat
{
    public Rect windowRect = new Rect(20, 20, 250, 400);
    private static GUI.WindowFunction DoWindow_il2cpp;
    
    public Menu()
    {
        DoWindow_il2cpp = Il2CppInterop.Runtime.DelegateSupport.ConvertDelegate<GUI.WindowFunction>(DoWindow);
    }

    public void OnGui()
    {
        if (ImguiManager._instance.isBaseWindowOpen)
        {
            windowRect = GUILayout.Window(0, windowRect, DoWindow_il2cpp, "CheaterCheetahCheat menu");
        }
    }
    
    void DoWindow(int windowID)
    {
        
        GUI.DragWindow(new Rect(0, 0, 1000, 20));
        Spammer.Enabled = GUILayout.Toggle(Spammer.Enabled, "chat spammer");
        GUILayout.BeginHorizontal();
        Spammer.Delay = GUILayout.HorizontalSlider(Spammer.Delay, 0.1f, 5f);
        GUILayout.Label($"{Spammer.Delay*1000:0} ms");
        GUILayout.EndHorizontal();
        VoiceHold.Enabled = GUILayout.Toggle(VoiceHold.Enabled, "open microphone");
        Nospread.Enabled = GUILayout.Toggle(Nospread.Enabled, "sv nospread");
        BypassLegit.Enabled = GUILayout.Toggle(BypassLegit.Enabled, "bypass legit");
        ChatOverlay.Enabled = GUILayout.Toggle(ChatOverlay.Enabled, "chat overlay");
        BypassLobbySize.Enabled = GUILayout.Toggle(BypassLobbySize.Enabled, "bypass lobby size (broken)");
        GUILayout.Label("Hi LWSS!");
    }
}