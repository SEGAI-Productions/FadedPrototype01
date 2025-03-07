#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CoverComponent.h"
#include "CoverGameplayAbility.generated.h"

/**
 * Base class for all cover system gameplay abilities
 */
UCLASS()
class COVERSYSTEM_API UCoverGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UCoverGameplayAbility();
	
	// Returns the cover component of the avatar actor
	UFUNCTION(BlueprintCallable, Category = "Cover")
	UCoverComponent* GetCoverComponent() const;
	
	// Returns true if the avatar actor is in cover
	UFUNCTION(BlueprintCallable, Category = "Cover")
	bool IsInCover() const;
	
protected:
	// The gameplay tag for this ability
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cover")
	FGameplayTag AbilityTag;
	
	// Whether this ability can only be used while in cover
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cover")
	bool bRequiresInCover;
	
	// Whether this ability can only be used while not in cover
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cover")
	bool bRequiresNotInCover;
	
	// Override to add additional checks for the ability
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
}; 