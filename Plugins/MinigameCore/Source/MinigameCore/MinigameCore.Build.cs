// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MinigameCore : ModuleRules
{
	public MinigameCore(ReadOnlyTargetRules Target) : base(Target)
	{
		bUsePrecompiled = true;
		
		PublicIncludePaths.AddRange(
			new string[] {
			});
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "BashCore", "LimbitlessBluetoothPlugin",
				"LevelSequence", "MovieScene",
				"UMG", "InputCore", "EnhancedInput", "CustomizableObject",
				"AIModule"
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
