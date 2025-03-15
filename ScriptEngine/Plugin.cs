using System.Collections;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Text;
using BepInEx;
using BepInEx.Bootstrap;
using BepInEx.Configuration;
using BepInEx.Logging;
using BepInEx.Unity.IL2CPP;
using HarmonyLib;
using Il2CppDumper;
using Mono.Cecil;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.UI;
using Logger = UnityEngine.Logger;
using Object = UnityEngine.Object;

namespace ScriptEngine;


[BepInPlugin(GUID, "Script Engine", "1.0.0")]
public class Plugin : BasePlugin
{
    public const string GUID = "com.bepis.bepinex.scriptengine";
    public const string Version = "1.0.0";
    public static IL2CPPChainloader Chainloader = IL2CPPChainloader.Instance;

    public string ScriptDirectory => Path.Combine(Paths.BepInExRootPath, "scripts");

    // private GameObject scriptManager;

    private ConfigEntry<bool> LoadOnStart { get; set; }
    // private ConfigEntry<KeyboardShortcut> ReloadKey { get; set; }
    private ConfigEntry<bool> QuietMode { get; set; }
    private ConfigEntry<bool> EnableFileSystemWatcher { get; set; }
    private ConfigEntry<bool> IncludeSubdirectories { get; set; }
    private ConfigEntry<float> AutoReloadDelay { get; set; }

    private ConfigEntry<bool> DumpAssemblies { get; set; }
    // private static readonly string DumpedAssembliesPath = Utility.CombinePaths(Paths.BepInExRootPath, "ScriptEngineDumpedAssemblies");

    private FileSystemWatcher fileSystemWatcher;
    private bool shouldReload;
    private float autoReloadTimer;
    private List<PluginInfo> plugins;
    private static Plugin instance;

    public override void Load()
    {
        instance = this;
        LoadOnStart = Config.Bind("General", "LoadOnStart", false, new ConfigDescription("Load all plugins from the scripts folder when starting the application. This is done from inside of Chainloader's Awake, therefore not all plugis might be loaded yet. BepInDependency attributes are ignored."));
        // ReloadKey = Config.Bind("General", "ReloadKey", new KeyboardShortcut(KeyCode.F6), new ConfigDescription("Press this key to reload all the plugins from the scripts folder"));
        QuietMode = Config.Bind("General", "QuietMode", false, new ConfigDescription("Disable all logging except for error messages."));
        IncludeSubdirectories = Config.Bind("General", "IncludeSubdirectories", false, new ConfigDescription("Also load plugins from subdirectories of the scripts folder."));
        EnableFileSystemWatcher = Config.Bind("AutoReload", "EnableFileSystemWatcher", false, new ConfigDescription("Watches the scripts directory for file changes and automatically reloads all plugins if any of the files gets changed (added/removed/modified)."));
        AutoReloadDelay = Config.Bind("AutoReload", "AutoReloadDelay", 3.0f, new ConfigDescription("Delay in seconds from detecting a change to files in the scripts directory to plugins being reloaded. Affects only EnableFileSystemWatcher."));
        DumpAssemblies = Config.Bind<bool>("AutoReload", "DumpAssemblies", false, "If enabled, BepInEx will save patched assemblies & symbols into BepInEx/ScriptEngineDumpedAssemblies.\nThis can be used by developers to inspect and debug plugins loaded by ScriptEngine.");

        // if (Directory.Exists(DumpedAssembliesPath))
        //     Directory.Delete(DumpedAssembliesPath, true);

        if (LoadOnStart.Value)
            ReloadPlugins();

        // if (EnableFileSystemWatcher.Value)
        //     StartFileSystemWatcher();

        try {
            var harmony = new Harmony(GUID);
            var originalUpdate = AccessTools.Method(typeof(RenderTextureManager), "Update");
            Log.LogMessage("[Trainer] Harmony - Original Method: " + originalUpdate.DeclaringType.Name + "." +
                           originalUpdate.Name);
            var postUpdate = AccessTools.Method(typeof(Plugin), "Update");
            Log.LogMessage("[Trainer] Harmony - Postfix Method: " + postUpdate.DeclaringType.Name + "." +
                           postUpdate.Name);
            harmony.Patch(originalUpdate, postfix: new HarmonyMethod(postUpdate));
            Log.LogMessage("[Trainer] Harmony - Runtime Patch's Applied");
        }
        catch (Exception e)
        {
            Log.LogError("[Trainer] Harmony - FAILED to Apply Patch's:" + e);
        }
    }
    
    [HarmonyPostfix]
    private static void Update()
    {
        if (Keyboard.current.f6Key.wasPressedThisFrame)
        {
            instance.Log.LogMessage("running plugin reload");
            instance.ReloadPlugins();
        }
        // else if (shouldReload)
        else if (false)
        {
            instance.autoReloadTimer -= Time.unscaledDeltaTime;
            if (instance.autoReloadTimer <= .0f)
                instance.ReloadPlugins();
        }
    }

    private static void TryRunModuleCtor(PluginInfo plugin, Assembly assembly)
    {
        try
        {
            RuntimeHelpers.RunModuleConstructor(assembly.GetType(plugin.TypeName).Module.ModuleHandle);
        }
        catch (Exception e)
        {
            instance.Log.LogMessage($"Couldn't run Module constructor for {assembly.FullName}::{plugin.TypeName}: {e}");
        }
    }
    private void ReloadPlugins()
    {
        shouldReload = false;

        // if (scriptManager != null)
        // {
            if (!QuietMode.Value) Log.LogMessage("Unloading old plugin instances");
            plugins = Chainloader.Plugins.Values.ToList();
            foreach (var plugin in plugins)
            {
                var metadataGUID = plugin.Metadata.GUID;
                if (metadataGUID == GUID) continue;
                if (plugin.Instance != null)
                    ((BasePlugin)plugin.Instance).Unload();
                plugin.GetType().GetProperty("Instance")
                    .SetValue(plugin, null, null);
                Chainloader.Plugins.Remove(metadataGUID);
            }

            // Object.Destroy(scriptManager);
        // }

        // scriptManager = new GameObject($"ScriptEngine_{DateTime.Now.Ticks}");
        // Object.DontDestroyOnLoad(scriptManager);
        Log.LogMessage("reloading plugins...");
        var p = plugins.Where(x => x.Metadata.GUID != GUID).ToList();
        // MethodInfo dynMethod;
        // try
        // {
        //     var methods = Chainloader.GetType().BaseType.GetMethods(
        //         BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Static);
        //     
        //     Log.LogMessage($"{methods.Length} {methods}");
        //     foreach (var method in methods)
        //     {
        //         Log.LogMessage($"{method.Name} {method.Attributes} {method.IsPrivate} {method.ReturnType}");
        //     }
        //     dynMethod = methods.Where(p =>
        //         // p.GetParameters().Select(q => q.ParameterType).SequenceEqual(new Type[] { typeof(IList<PluginInfo>) })
        //         // && p.ReturnType == typeof(IList<PluginInfo>)
        //         p.IsPrivate
        //         && p.Name == "LoadPlugins"
        //     ).First();
        // }
        // catch (Exception e)
        // {
        //     Log.LogMessage("reflection failed. " + e);
        //     return;
        // }
        // dynMethod.Invoke(Chainloader, new object[] { p });
        foreach (var plugin in p)
        {
            LoadDLL(plugin.Location);
        }
        // var files = Directory.GetFiles(ScriptDirectory, "*.dll", IncludeSubdirectories.Value ? SearchOption.AllDirectories : SearchOption.TopDirectoryOnly);
        // if (files.Length > 0)
        // {
        //     foreach (string path in files)
        //         LoadDLL(path, scriptManager);
        //
        //     if (!QuietMode.Value)
        //         Log.LogMessage("Reloaded all plugins!");
        // }
        // else
        // {
        //     if (!QuietMode.Value)
        //         Log.LogMessage("No plugins to reload");
        // }
    }

    private void LoadDLL(string path)
    {
        var defaultResolver = new DefaultAssemblyResolver();
        defaultResolver.AddSearchDirectory(ScriptDirectory);
        defaultResolver.AddSearchDirectory(Paths.ManagedPath);
        defaultResolver.AddSearchDirectory(Paths.BepInExAssemblyDirectory);
    
        if (!QuietMode.Value)
            Log.LogMessage($"Loading plugins from {path}");
    
        using (var dll = AssemblyDefinition.ReadAssembly(path, new ReaderParameters {
            AssemblyResolver = defaultResolver,
            // ReadSymbols = true
        }))
        {
            dll.Name.Name = $"{dll.Name.Name}-{DateTime.Now.Ticks}";
            Assembly ass;
    
            // if (DumpAssemblies.Value)
            // {
            //     // Dump assembly & load it from disk
            //     if (!Directory.Exists(DumpedAssembliesPath))
            //         Directory.CreateDirectory(DumpedAssembliesPath);
            //
            //     string assemblyDumpPath = Path.Combine(DumpedAssembliesPath, dll.Name.Name + Path.GetExtension(dll.MainModule.Name));
            //
            //     using (FileStream outFileStream = new FileStream(assemblyDumpPath, FileMode.Create))
            //     {
            //         dll.Write((Stream)outFileStream, new WriterParameters()
            //         {
            //             WriteSymbols = true
            //         });
            //     }
            //
            //     ass = Assembly.LoadFile(assemblyDumpPath);
            //     if (!QuietMode.Value)
            //         Log.LogMessage($"Loaded dumped Assembly from {assemblyDumpPath}");
            // } else
            {
                // Load from memory
                using (var ms = new MemoryStream())
                {
                    dll.Write(ms);
                    ass = Assembly.Load(ms.ToArray());
                }
            }
    
    
            foreach (Type type in GetTypesSafe(ass))
            {
                try
                {
                    if (!typeof(BasePlugin).IsAssignableFrom(type)) continue;
    
                    var metadata = MetadataHelper.GetMetadata(type);
                    if (metadata == null) continue;
    
                    if (!QuietMode.Value)
                        Log.LogMessage($"Loading {metadata.GUID}");
    
                    if (Chainloader.Plugins.TryGetValue(metadata.GUID, out var existingPluginInfo))
                        throw new InvalidOperationException($"A plugin with GUID {metadata.GUID} is already loaded! ({existingPluginInfo.Metadata.Name} v{existingPluginInfo.Metadata.Version})");
    
                    var typeDefinition = dll.MainModule.Types.First(x => x.FullName == type.FullName);
                    var pluginInfo = IL2CPPChainloader.ToPluginInfo(typeDefinition, path);
                    
                    
                    Chainloader.Plugins[pluginInfo.Metadata.GUID] = pluginInfo;
                    TryRunModuleCtor(pluginInfo, ass);
                    var newPluginInstance = Chainloader.LoadPlugin(pluginInfo, ass);
                    pluginInfo.GetType().GetProperty("Instance")
                        .SetValue(pluginInfo, newPluginInstance, null);
                }
                catch (Exception e)
                {
                    Log.LogMessage($"Failed to load plugin {type.Name} because of exception: {e}");
                }
            }
        }
    }

    private void StartFileSystemWatcher()
    {
        fileSystemWatcher = new FileSystemWatcher(ScriptDirectory)
        {
            IncludeSubdirectories = IncludeSubdirectories.Value
        };
        fileSystemWatcher.NotifyFilter = NotifyFilters.LastWrite | NotifyFilters.FileName;
        fileSystemWatcher.Filter = "*.dll";
        fileSystemWatcher.Changed += FileChangedEventHandler;
        fileSystemWatcher.Deleted += FileChangedEventHandler;
        fileSystemWatcher.Created += FileChangedEventHandler;
        fileSystemWatcher.Renamed += FileChangedEventHandler;
        fileSystemWatcher.EnableRaisingEvents = true;
    }

    private void FileChangedEventHandler(object sender, FileSystemEventArgs args)
    {
        if (!QuietMode.Value)
            Log.LogMessage($"File {Path.GetFileName(args.Name)} changed. Delayed recompiling...");
        shouldReload = true;
        autoReloadTimer = AutoReloadDelay.Value;
    }

    private IEnumerable<Type> GetTypesSafe(Assembly ass)
    {
        try
        {
            return ass.GetTypes();
        }
        catch (ReflectionTypeLoadException ex)
        {
            var sbMessage = new StringBuilder();
            sbMessage.AppendLine("\r\n-- LoaderExceptions --");
            foreach (var l in ex.LoaderExceptions)
                sbMessage.AppendLine(l.ToString());
            sbMessage.AppendLine("\r\n-- StackTrace --");
            sbMessage.AppendLine(ex.StackTrace);
            Log.LogMessage(sbMessage.ToString());
            return ex.Types.Where(x => x != null);
        }
    }

    private IEnumerator DelayAction(Action action)
    {
        yield return null;
        action();
    }
}