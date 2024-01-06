// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_JackOLantern : ModuleRules
{
	public Project_JackOLantern(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Niagara" });
	}
}
