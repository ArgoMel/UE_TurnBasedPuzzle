// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class TurnBasedPuzzle : ModuleRules
{
	public TurnBasedPuzzle(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"AIModule",
			"GameplayTasks",
			"UMG",
			"EnhancedInput",
			"Niagara" 
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

	}
}
