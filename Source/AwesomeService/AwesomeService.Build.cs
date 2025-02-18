using UnrealBuildTool;

public class AwesomeService : ModuleRules
{
	public AwesomeService(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "CoreUObject",
            });

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Engine",
				"Slate",
				"SlateCore",
			});


        if (Target.bBuildEditor == true)
        {
            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                    "UnrealEd"
                });
        }
    }
}
