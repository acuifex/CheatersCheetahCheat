using CheatersCheetahCheat.cheats;
using UnityEngine;
using UnityEngine.InputSystem;

namespace CheatersCheetahCheat;

public class CheatObject : MonoBehaviour
{
    private static List<ICheat> cheats = new ();
    
    public CheatObject(IntPtr ptr) : base(ptr)
    {
        Plugin.log.LogMessage("[Trainer] Entered Constructor");
        cheats.Clear();
        cheats.Add(new Spammer());
        cheats.Add(new Nospread());
        cheats.Add(new BypassLegit());
        cheats.Add(new VoiceHold());
        cheats.Add(new cheats.Menu());
        cheats.Add(new ChatOverlay());
        cheats.Add(new BypassLobbySize());
    }

    public void Awake()
    {
        Plugin.log.LogMessage("[Trainer] I'm awake!");
        foreach (ICheat cheat in cheats)
        {
            cheat.Awake();
        }
    }

    // Harmony Patch's must be static!
    // [HarmonyPostfix]
    public void Start() 
    {
        Plugin.log.LogMessage("[Trainer] I'm started!");
        foreach (ICheat cheat in cheats)
        {
            cheat.Start();
        }
    }
 
 
    // [HarmonyPostfix]
    public void Update()
    {
        //BepInExLoader.log.LogMessage("[Trainer] I'm Updating, disable this message after testing.");
			
        // Plugin.log.LogMessage("[Trainer] boop1");
        // Note the difference for getting keypress.
        // if (Keyboard.current.pKey.isPressed)
        // {
            // Plugin.log.LogMessage("[Trainer] boop6");
            // ImguiManager.ToggleMenu(false, false);
        // }

        foreach (ICheat cheat in cheats)
        {
            cheat.Update();
        }
    }

    public void OnGUI()
    {
        GUI.Label(new Rect(10, 10, 150, 200), "CheaterCheetahCheat!");
        foreach (ICheat cheat in cheats)
        {
            cheat.OnGui();
        }
    }
}