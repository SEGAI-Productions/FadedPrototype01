#pragma once

#include "CoreMinimal.h"
#include "CoverGameplayAbility.h"
#include "EnterCoverAbility.generated.h"

/**
 * Gameplay ability for entering cover
 */
UCLASS()
class COVERSYSTEM_API UEnterCoverAbility : public UCoverGameplayAbility
{
	GENERATED_BODY()
	
public:
	UEnterCoverAbility();
	
	// Called when the ability is activated
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	// Called when the ability ends
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
protected:
	// The animation montage to play when entering cover
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* EnterCoverMontage;
	
	// The time it takes to enter cover
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	float EnterCoverTime = 0.5f;
	
	// The maximum distance to search for cover
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cover")
	float MaxCoverSearchDistance = 200.0f;
}; 