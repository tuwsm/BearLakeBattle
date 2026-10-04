using UnrealBuildTool;

public class LimbitlessBTAndroid : ModuleRules
{
    public LimbitlessBTAndroid(ReadOnlyTargetRules Target) : base(Target)
    {
        bUsePrecompiled = true; 
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "LimbitlessBluetoothPlugin", "BleUtilities",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "BleUtilities", 
                "AndroidPermission"
            }
        );
    }
}