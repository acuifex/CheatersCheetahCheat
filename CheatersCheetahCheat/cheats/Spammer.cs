using GlobalUI;
using UnityEngine;
using UnityEngine.InputSystem;
using Object = UnityEngine.Object;
using Random = UnityEngine.Random;

namespace CheatersCheetahCheat.cheats;

public class Spammer : ICheat
{
    private float lastMessageTime = 0;
    public static bool Enabled = false;
    public static float Delay = 0.850f;
    public List<string> messages = new List<string>
    {
        "AimTux owns me and all",
        "Your Windows p2c sucks my AimTux dry",
        "It's free as in FREEDOM!",
        "Tux only let me out so I could play this game, please be nice!",
        "Tux nutted but you keep sucken",
        ">tfw no vac on Linux",
        "Cathook - more fun than a ball of yarn!",
        "GNU/Linux is the best OS!",
        "Visit https://cathook.club for more information!",
        "Cathook - Free and Open-Source tf2 cheat!",
        "Cathook - ca(n)t stop me meow!"
    };
    TextChatComponent textChatComponent;
    public void Update()
    {
        if (Keyboard.current.numpad2Key.wasPressedThisFrame)
        {
            Enabled = !Enabled;
            Plugin.log.LogMessage("[Trainer] toggling spammer:" + Enabled);
        }
        if (!textChatComponent)
        {
            textChatComponent = Object.FindObjectOfType<TextChatComponent>(true);
            Plugin.log.LogMessage($"spammer: {textChatComponent}");
        }
        if (Enabled && textChatComponent && lastMessageTime < Time.time-Delay)
        {
            lastMessageTime = Time.time;
            textChatComponent.ToggleChatMode(true);
            var message = messages[Random.Range(0, messages.Count)];
            textChatComponent.OnMessageSubmit(message);
        }
    }
}