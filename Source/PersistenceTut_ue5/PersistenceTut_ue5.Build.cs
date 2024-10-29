// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PersistenceTut_ue5 : ModuleRules
{
	public PersistenceTut_ue5(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "HeadMountedDisplay", "Http", "Json", "JsonUtilities" });
	}
}
