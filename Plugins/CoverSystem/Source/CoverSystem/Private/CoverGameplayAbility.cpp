#include "CoverGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"

UCoverGameplayAbility::UCoverGameplayAbility()
{
	// Default values
	bRequiresInCover = false;
	bRequiresNotInCover = false;
	
	// Set the instancing policy to instance per actor
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

UCoverComponent* UCoverGameplayAbility::GetCoverComponent() const
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (!AvatarActor)
	{
		return nullptr;
	}
	
	return AvatarActor->FindComponentByClass<UCoverComponent>();
}

bool UCoverGameplayAbility::IsInCover() const
{
	UCoverComponent* CoverComp = GetCoverComponent();
	if (!CoverComp)
	{
		return false;
	}
	
	return CoverComp->IsInCover();
}

bool UCoverGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	// Check if the base class allows activation
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	
	// Get the avatar actor
	AActor* AvatarActor = ActorInfo->AvatarActor.Get();
	if (!AvatarActor)
	{
		return false;
	}
	
	// Get the cover component
	UCoverComponent* CoverComp = AvatarActor->FindComponentByClass<UCoverComponent>();
	if (!CoverComp)
	{
		return false;
	}
	
	// Check if the ability requires the actor to be in cover
	if (bRequiresInCover && !CoverComp->IsInCover())
	{
		return false;
	}
	
	// Check if the ability requires the actor to not be in cover
	if (bRequiresNotInCover && CoverComp->IsInCover())
	{
		return false;
	}
	
	return true;
} 