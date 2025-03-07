#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "CoverSystemManager.generated.h"

class UCoverComponent;

/**
 * Manager class for the cover system
 */
UCLASS(Blueprintable, BlueprintType)
class COVERSYSTEM_API UCoverSystemManager : public UObject
{
	GENERATED_BODY()
	
public:
	UCoverSystemManager();
	
	// Initialize the cover system manager
	void Initialize();
	
	// Get the cover system manager instance
	UFUNCTION(BlueprintCallable, Category = "Cover System", meta = (WorldContext = "WorldContextObject"))
	static UCoverSystemManager* GetInstance(UObject* WorldContextObject);
	
	// Register a cover component
	UFUNCTION(BlueprintCallable, Category = "Cover System")
	void RegisterCoverComponent(UCoverComponent* CoverComponent);
	
	// Unregister a cover component
	UFUNCTION(BlueprintCallable, Category = "Cover System")
	void UnregisterCoverComponent(UCoverComponent* CoverComponent);
	
	// Get all registered cover components
	UFUNCTION(BlueprintCallable, Category = "Cover System")
	TArray<UCoverComponent*> GetAllCoverComponents() const;
	
	// Get all cover components in range
	UFUNCTION(BlueprintCallable, Category = "Cover System")
	TArray<UCoverComponent*> GetCoverComponentsInRange(const FVector& Location, float Range) const;
	
	// Register gameplay tags
	void RegisterGameplayTags();
	
private:
	// The singleton instance
	static UCoverSystemManager* Instance;
	
	// The registered cover components
	UPROPERTY()
	TArray<UCoverComponent*> RegisteredCoverComponents;
}; 