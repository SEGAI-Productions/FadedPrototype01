#include "EnterCoverAbility.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "CoverComponent.h"

UEnterCoverAbility::UEnterCoverAbility()
{
	// Set the ability tag
	AbilityTag = FGameplayTag::RequestGameplayTag(FName("Ability.Cover.Enter"));
	
	// This ability requires the actor to not be in cover
	bRequiresNotInCover = true;
	
	// Set the ability tags
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag = AbilityTag;
	AbilityTriggers.Add(TriggerData);
	
	// Set the ability tags
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Cover.Entering")));
}

void UEnterCoverAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	// Call the base class implementation
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	// Get the avatar actor
	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	if (!Character)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	// Get the cover component
	UCoverComponent* CoverComp = GetCoverComponent();
	if (!CoverComp)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	// Find cover nearby
	FVector CoverLocation;
	FVector CoverNormal;
	if (!CoverComp->FindCoverNearby(CoverLocation, CoverNormal))
	{
		// No cover found
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	// Play the enter cover montage if available
	if (EnterCoverMontage)
	{
		Character->PlayAnimMontage(EnterCoverMontage);
	}
	
	// Schedule the ability to end after the enter cover time
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([this, Handle, ActorInfo, ActivationInfo, CoverComp, CoverLocation, CoverNormal]()
	{
		// Enter cover
		CoverComp->EnterCover(CoverLocation, CoverNormal);
		
		// End the ability
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	});
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, EnterCoverTime, false);
}

void UEnterCoverAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// If the ability was cancelled, stop the montage
	if (bWasCancelled)
	{
		ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
		if (Character && EnterCoverMontage)
		{
			Character->StopAnimMontage(EnterCoverMontage);
		}
	}
	
	// Call the base class implementation
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
} 