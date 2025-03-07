#include "CoverSystem.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FCoverSystemModule"

void FCoverSystemModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(LogTemp, Log, TEXT("CoverSystem module has been loaded"));
}

void FCoverSystemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UE_LOG(LogTemp, Log, TEXT("CoverSystem module has been unloaded"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCoverSystemModule, CoverSystem) 