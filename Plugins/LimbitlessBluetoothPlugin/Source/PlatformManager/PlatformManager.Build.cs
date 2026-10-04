using UnrealBuildTool;

public class PlatformManager : ModuleRules
{
    public PlatformManager(ReadOnlyTargetRules Target) : base(Target)
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
            }
        );

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PrivateDependencyModuleNames.Add("LimbitlessBTWindows");
        }

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateDependencyModuleNames.Add("BleUtilities");
        }
    }
}