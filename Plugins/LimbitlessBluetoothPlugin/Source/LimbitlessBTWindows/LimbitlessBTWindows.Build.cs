using UnrealBuildTool;
using System.IO;

public class LimbitlessBTWindows : ModuleRules
{
    public LimbitlessBTWindows(ReadOnlyTargetRules Target) : base(Target)
    {
        bUsePrecompiled = true;
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "LimbitlessBluetoothPlugin",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "WinBT"
            }
        );
        
        string windowsSdkVersion = Target.WindowsPlatform.WindowsSdkVersion;
        string windowsSdkPath = Target.WindowsPlatform.WindowsSdkDir;
		
        if (!string.IsNullOrEmpty(windowsSdkVersion) && !string.IsNullOrEmpty(windowsSdkPath))
        {
            string WinRTIncludePath = Path.Combine(windowsSdkPath, "Include", windowsSdkVersion, "cppwinrt");

            if (Directory.Exists(WinRTIncludePath))
            {
                PublicSystemIncludePaths.Add(WinRTIncludePath);
            }
            else
            {
                throw new BuildException($"WinRT Include Path not found: {WinRTIncludePath}");
            }
        }

        PublicAdditionalLibraries.Add("windowsapp.lib");

        PublicSystemLibraries.Add("WindowsApp.lib");
    }
}