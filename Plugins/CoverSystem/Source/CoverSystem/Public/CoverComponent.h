#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpec.h"
#include "CoverComponent.generated.h"

class UGameplayAbility;
class UAbilitySystemComponent;

/**
 * Component that provides cover functionality to characters
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COVERSYSTEM_API UCoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCoverComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// The location of the current cover
	UPROPERTY(BlueprintReadOnly, Category = "Cover")
	FVector CurrentCoverLocation;

	// The normal vector of the current cover
	UPROPERTY(BlueprintReadOnly, Category = "Cover")
	FVector CurrentCoverNormal;

	// Whether the character is currently in cover
	UPROPERTY(BlueprintReadOnly, Category = "Cover")
	bool bIsInCover;

	// The ability system component of the owner
	UPROPERTY()
	UAbilitySystemComponent* OwnerAbilitySystemComponent;

	// The cover enter ability
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cover|Abilities")
	TSubclassOf<UGameplayAbility> EnterCoverAbility;

	// The cover exit ability
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cover|Abilities")
	TSubclassOf<UGameplayAbility> ExitCoverAbility;

	// The fire from cover ability
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cover|Abilities")
	TSubclassOf<UGameplayAbility> FireFromCoverAbility;

	// The blind fire from cover ability
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cover|Abilities")
	TSubclassOf<UGameplayAbility> BlindFireAbility;

	// The move to adjacent cover ability
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cover|Abilities")
	TSubclassOf<UGameplayAbility> MoveToAdjacentCoverAbility;

	// The gameplay tags for cover abilities
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cover|Tags")
	FGameplayTag EnterCoverTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cover|Tags")
	FGameplayTag ExitCoverTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cover|Tags")
	FGameplayTag FireFromCoverTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cover|Tags")
	FGameplayTag BlindFireTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cover|Tags")
	FGameplayTag MoveToAdjacentCoverTag;

	// The trace distance for finding cover
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cover|Settings")
	float CoverTraceDistance = 200.0f;

	// The minimum height required for cover
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cover|Settings")
	float MinCoverHeight = 100.0f;

	// The maximum angle (in degrees) that cover can be at
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cover|Settings")
	float MaxCoverAngle = 45.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Returns true if the owner is currently in cover
	UFUNCTION(BlueprintCallable, Category = "Cover")
	bool IsInCover() const { return bIsInCover; }

	// Returns true if the owner can enter cover at the specified location
	UFUNCTION(BlueprintCallable, Category = "Cover")
	bool CanEnterCover(const FVector& CoverLocation, const FVector& CoverNormal) const;

	// Attempts to find cover near the owner
	UFUNCTION(BlueprintCallable, Category = "Cover")
	bool FindCoverNearby(FVector& OutCoverLocation, FVector& OutCoverNormal);

	// Attempts to enter cover at the specified location
	UFUNCTION(BlueprintCallable, Category = "Cover")
	bool EnterCover(const FVector& CoverLocation, const FVector& CoverNormal);

	// Exits cover
	UFUNCTION(BlueprintCallable, Category = "Cover")
	void ExitCover();

	// Fires weapon from cover
	UFUNCTION(BlueprintCallable, Category = "Cover")
	void FireFromCover();

	// Blind fires weapon from cover
	UFUNCTION(BlueprintCallable, Category = "Cover")
	void BlindFireFromCover();

	// Moves to adjacent cover
	UFUNCTION(BlueprintCallable, Category = "Cover")
	bool MoveToAdjacentCover(const FVector& NewCoverLocation, const FVector& NewCoverNormal);

	// Grants the cover abilities to the owner
	UFUNCTION(BlueprintCallable, Category = "Cover")
	void GrantCoverAbilities();

private:
	// Activates an ability by tag
	bool ActivateAbilityByTag(const FGameplayTag& AbilityTag);

	// Gets the ability system component of the owner
	UAbilitySystemComponent* GetOwnerAbilitySystemComponent();
}; 