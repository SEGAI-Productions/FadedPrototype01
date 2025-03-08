#include "FadedCore.h"
#include "GameplayTagsManager.h"

#define LOCTEXT_NAMESPACE "FFadedCoreModule"

void FFadedCoreModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(LogTemp, Log, TEXT("FadedCore module has been loaded"));
	
	// Register the gameplay tags
	UGameplayTagsManager& TagManager = UGameplayTagsManager::Get();
	
	// Register the tags
	TagManager.AddNativeGameplayTag(FName("Faded.Abilities.Movement.Dodge"));
	TagManager.AddNativeGameplayTag(FName("Faded.Abilities.Movement.Cover"));
	
	// Ensure all tags are registered
	TagManager.DoneAddingNativeTags();
}

void FFadedCoreModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UE_LOG(LogTemp, Log, TEXT("FadedCore module has been unloaded"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFadedCoreModule, FadedCore) 