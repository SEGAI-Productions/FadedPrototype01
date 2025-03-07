#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "CoverSystemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UCoverSystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for actors that can use the cover system
 */
class COVERSYSTEM_API ICoverSystemInterface
{
	GENERATED_BODY()

public:
	/** Returns true if the actor is currently in cover */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cover System")
	bool IsInCover() const;
	
	/** Returns true if the actor can enter cover at the specified location */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cover System")
	bool CanEnterCover(const FVector& CoverLocation, const FVector& CoverNormal) const;
	
	/** Attempts to enter cover at the specified location */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cover System")
	bool EnterCover(const FVector& CoverLocation, const FVector& CoverNormal);
	
	/** Exits cover */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cover System")
	void ExitCover();
	
	/** Fires weapon from cover */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cover System")
	void FireFromCover();
	
	/** Blind fires weapon from cover */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cover System")
	void BlindFireFromCover();
	
	/** Moves to adjacent cover */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cover System")
	bool MoveToAdjacentCover(const FVector& NewCoverLocation, const FVector& NewCoverNormal);
}; 