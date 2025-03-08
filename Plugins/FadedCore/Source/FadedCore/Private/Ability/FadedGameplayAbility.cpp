// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/FadedGameplayAbility.h"

#include "AbilitySystemLog.h"
#include "Curves/CurveVector.h"
#include "AbilitySystemGlobals.h"
#include "BlueprintGameplayTagLibrary.h"
#include "Subsystems/CooldownSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FadedGameplayAbility)

#define ENSURE_ABILITY_IS_INSTANTIATED_OR_RETURN(FunctionName, ReturnValue)																				\
{																																						\
	if (!ensure(IsInstantiated()))																														\
	{																																					\
		ABILITY_LOG(Error, TEXT("%s: " #FunctionName " cannot be called on a non-instanced ability. Check the instancing policy."), *GetPathName());	\
		return ReturnValue;																																\
	}																																					\
}

UFadedGameplayAbility::UFadedGameplayAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

bool UFadedGameplayAbility::CheckCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	bool bNoCooldown = Super::CheckCooldown(Handle, ActorInfo, OptionalRelevantTags);

	if (bNoCooldown && (GlobalCooldownDuration > 0 || CooldownDuration > 0))
	{
		UWorld* World = GetWorld();
		UGameInstance* GameInstance = (World != nullptr) ? World->GetGameInstance() : nullptr;
		UCooldownSubsystem* CooldownSubsystem = (GameInstance != nullptr) ? GameInstance->GetSubsystem<UCooldownSubsystem>() : nullptr;
		AActor* OwnerActor = CurrentActorInfo->OwnerActor.Get();
		if (CooldownSubsystem && OwnerActor)
		{
			bNoCooldown = !CooldownSubsystem->IsOnCooldown(GetClass(), OwnerActor);
		}
	}

	return bNoCooldown;
}

void UFadedGameplayAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCooldown(Handle, ActorInfo, ActivationInfo);

	UWorld* World = GetWorld();
	UGameInstance* GameInstance = (World != nullptr) ? World->GetGameInstance() : nullptr;
	UCooldownSubsystem* CooldownSubsystem = (GameInstance != nullptr) ? GameInstance->GetSubsystem<UCooldownSubsystem>() : nullptr;
	AActor* OwnerActor = CurrentActorInfo->OwnerActor.Get();
	if (CooldownSubsystem && OwnerActor)
	{
		if (GlobalCooldownDuration > 0)
		{
			CooldownSubsystem->ApplyGlobalCooldown(GetClass(), OwnerActor, GlobalCooldownDuration);
		}

		if (CooldownDuration > 0)
		{
			CooldownSubsystem->ApplyCooldown(GetClass(), OwnerActor, CooldownDuration);
		}
	}
}
