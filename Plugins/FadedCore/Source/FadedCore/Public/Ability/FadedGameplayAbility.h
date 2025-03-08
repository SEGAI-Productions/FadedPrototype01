// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "FadedGameplayAbility.generated.h"

class UCurveVector;


/**
 * 
 */
UCLASS()
class FADEDCORE_API UFadedGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UFadedGameplayAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** Checks cooldown. returns true if we can be used again. False if not */
	virtual bool CheckCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	/** Applies CooldownGameplayEffect to the target */
	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;

	UPROPERTY(EditDefaultsOnly, Category = Cooldowns)
	float GlobalCooldownDuration = 0;

	UPROPERTY(EditDefaultsOnly, Category = Cooldowns)
	float CooldownDuration = 0;
};
