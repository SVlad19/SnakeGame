// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Snake : ModuleRules
{
    public Snake(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG" });

        if (Target.Configuration != UnrealTargetConfiguration.Shipping)
        {
            PublicDependencyModuleNames.Add("FunctionalTesting");
        }

        PrivateDependencyModuleNames.AddRange(new string[] { });

    }
}
