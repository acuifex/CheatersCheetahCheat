using HarmonyLib;
using UnityEngine.InputSystem;
using Vector3 = UnityEngine.Vector3;

namespace CheatersCheetahCheat.cheats;

public class Nospread : ICheat
{
    static public bool Enabled = false;
    
    [HarmonyPrefix]
    public static void SpreadAppliedAngle(Vector3 originEulerAngle, ref float spreadRange)
    {
        Plugin.log.LogMessage("[Trainer] spread called:" + Enabled + " " + spreadRange);
        if (Enabled)
        {
            spreadRange = 0;
        }

    }
    public void Update()
    {
        if (Keyboard.current.numpad1Key.wasPressedThisFrame)
        {
            Enabled = !Enabled;
            Plugin.log.LogMessage("[Trainer] toggling nospread:" + Enabled);
        }
    }
}