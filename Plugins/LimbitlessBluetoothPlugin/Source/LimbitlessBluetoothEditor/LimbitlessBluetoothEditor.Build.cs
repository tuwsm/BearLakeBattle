using UnrealBuildTool;

public class LimbitlessBluetoothEditor : ModuleRules
{
    public LimbitlessBluetoothEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        bUsePrecompiled = true;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "Blutility",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UMG",
                "Blutility",
                "UnrealEd",
                "EditorSubsystem",
                "LimbitlessBluetoothPlugin", 
                "PlatformManager",
            }
        );
    }
}