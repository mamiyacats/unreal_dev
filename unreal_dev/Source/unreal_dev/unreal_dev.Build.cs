// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class unreal_dev : ModuleRules
{
	public unreal_dev(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
