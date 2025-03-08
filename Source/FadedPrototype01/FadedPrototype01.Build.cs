using UnrealBuildTool;

public class FadedPrototype01 : ModuleRules {
	public FadedPrototype01(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"GameplayAbilities", 
			"GameplayTags", 
			"GameplayTasks",
			"FadedCore",
		});
		PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}
