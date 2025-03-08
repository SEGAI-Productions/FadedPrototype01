#include "CoverComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameplayTagsManager.h"
#include "NavigationSystem.h"

// Sets default values for this component's properties
UCoverComponent::UCoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame
	PrimaryComponentTick.bCanEverTick = true;

	// Initialize default values
	bIsInCover = false;
	CurrentCoverLocation = FVector::ZeroVector;
	CurrentCoverNormal = FVector::ZeroVector;
	
	// Initialize gameplay tags
	EnterCoverTag = FGameplayTag::RequestGameplayTag(FName("Faded.Abilities.Movement.Cover"));
	ExitCoverTag = FGameplayTag::RequestGameplayTag(FName("Faded.Abilities.Movement.Cover"));
	FireFromCoverTag = FGameplayTag::RequestGameplayTag(FName("Faded.Abilities.Movement.Cover"));
	BlindFireTag = FGameplayTag::RequestGameplayTag(FName("Faded.Abilities.Movement.Cover"));
	MoveToAdjacentCoverTag = FGameplayTag::RequestGameplayTag(FName("Faded.Abilities.Movement.Cover"));
}

// Called when the game starts
void UCoverComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Get the ability system component of the owner
	OwnerAbilitySystemComponent = GetOwnerAbilitySystemComponent();
	
	// Grant cover abilities to the owner
	GrantCoverAbilities();
}

// Called every frame
void UCoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If in cover, ensure the owner stays in the correct position
	if (bIsInCover)
	{
		ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
		if (OwnerCharacter)
		{
			// Calculate the desired position (slightly offset from the cover)
			FVector DesiredPosition = CurrentCoverLocation + (CurrentCoverNormal * 50.0f);
			
			// Keep the character's Z position
			DesiredPosition.Z = OwnerCharacter->GetActorLocation().Z;
			
			// Smoothly move the character to the desired position
			FVector CurrentPosition = OwnerCharacter->GetActorLocation();
			FVector NewPosition = FMath::VInterpTo(CurrentPosition, DesiredPosition, DeltaTime, 5.0f);
			
			// Update the character's position
			OwnerCharacter->SetActorLocation(NewPosition);
			
			// Ensure the character is facing away from the cover
			FRotator DesiredRotation = (-CurrentCoverNormal).Rotation();
			DesiredRotation.Pitch = 0.0f;
			DesiredRotation.Roll = 0.0f;
			
			// Smoothly rotate the character
			FRotator CurrentRotation = OwnerCharacter->GetActorRotation();
			FRotator NewRotation = FMath::RInterpTo(CurrentRotation, DesiredRotation, DeltaTime, 5.0f);
			
			// Update the character's rotation
			OwnerCharacter->SetActorRotation(NewRotation);
		}
	}
}

bool UCoverComponent::CanEnterCover(const FVector& CoverLocation, const FVector& CoverNormal) const
{
	// Check if the cover normal is valid (pointing up is not valid cover)
	if (CoverNormal.IsZero() || FMath::Abs(CoverNormal.Z) > FMath::Sin(FMath::DegreesToRadians(MaxCoverAngle)))
	{
		return false;
	}
	
	// Check if there's enough space for the character
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter)
	{
		return false;
	}
	
	// Calculate the position behind the cover
	FVector BehindCoverPosition = CoverLocation + (CoverNormal * 100.0f);
	
	// Check if the position is reachable
	FNavLocation NavLocation;
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (NavSystem && !NavSystem->ProjectPointToNavigation(BehindCoverPosition, NavLocation, FVector(100.0f, 100.0f, 100.0f)))
	{
		return false;
	}
	
	// Check if the cover is tall enough
	FHitResult HitResult;
	FVector TraceStart = CoverLocation + FVector(0.0f, 0.0f, 50.0f);
	FVector TraceEnd = TraceStart + (-CoverNormal * 50.0f);
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());
	
	if (!GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{
		return false;
	}
	
	// Check the height of the cover
	FVector UpTraceStart = CoverLocation;
	FVector UpTraceEnd = UpTraceStart + FVector(0.0f, 0.0f, MinCoverHeight);
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, UpTraceStart, UpTraceEnd, ECC_Visibility, QueryParams))
	{
		return false;
	}
	
	return true;
}

bool UCoverComponent::FindCoverNearby(FVector& OutCoverLocation, FVector& OutCoverNormal)
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter)
	{
		return false;
	}
	
	// Get the character's forward vector
	FVector ForwardVector = OwnerCharacter->GetActorForwardVector();
	
	// Get the character's location
	FVector CharacterLocation = OwnerCharacter->GetActorLocation();
	
	// Trace in front of the character to find potential cover
	FHitResult HitResult;
	FVector TraceStart = CharacterLocation;
	FVector TraceEnd = TraceStart + (ForwardVector * CoverTraceDistance);
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());
	
	// Draw debug line
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 2.0f, 0, 1.0f);
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{
		// Found a potential cover object
		OutCoverLocation = HitResult.Location;
		OutCoverNormal = HitResult.Normal;
		
		// Check if this is valid cover
		if (CanEnterCover(OutCoverLocation, OutCoverNormal))
		{
			// Draw debug sphere at cover location
			DrawDebugSphere(GetWorld(), OutCoverLocation, 10.0f, 12, FColor::Blue, false, 2.0f, 0, 1.0f);
			
			// Draw debug arrow for cover normal
			DrawDebugDirectionalArrow(GetWorld(), OutCoverLocation, OutCoverLocation + (OutCoverNormal * 50.0f), 
				10.0f, FColor::Red, false, 2.0f, 0, 1.0f);
			
			return true;
		}
	}
	
	return false;
}

bool UCoverComponent::EnterCover(const FVector& CoverLocation, const FVector& CoverNormal)
{
	// Check if we can enter cover at this location
	if (!CanEnterCover(CoverLocation, CoverNormal))
	{
		return false;
	}
	
	// Store the cover information
	CurrentCoverLocation = CoverLocation;
	CurrentCoverNormal = CoverNormal;
	bIsInCover = true;
	
	// Modify the character's movement
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter && OwnerCharacter->GetCharacterMovement())
	{
		// Disable character rotation with movement
		OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
		
		// Reduce movement speed while in cover
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	}
	
	// Activate the enter cover ability
	ActivateAbilityByTag(EnterCoverTag);
	
	return true;
}

void UCoverComponent::ExitCover()
{
	if (!bIsInCover)
	{
		return;
	}
	
	// Reset cover information
	CurrentCoverLocation = FVector::ZeroVector;
	CurrentCoverNormal = FVector::ZeroVector;
	bIsInCover = false;
	
	// Restore the character's movement
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter && OwnerCharacter->GetCharacterMovement())
	{
		// Re-enable character rotation with movement
		OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
		
		// Restore normal movement speed
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
	
	// Activate the exit cover ability
	ActivateAbilityByTag(ExitCoverTag);
}

void UCoverComponent::FireFromCover()
{
	if (!bIsInCover)
	{
		return;
	}
	
	// Activate the fire from cover ability
	ActivateAbilityByTag(FireFromCoverTag);
}

void UCoverComponent::BlindFireFromCover()
{
	if (!bIsInCover)
	{
		return;
	}
	
	// Activate the blind fire ability
	ActivateAbilityByTag(BlindFireTag);
}

bool UCoverComponent::MoveToAdjacentCover(const FVector& NewCoverLocation, const FVector& NewCoverNormal)
{
	if (!bIsInCover)
	{
		return false;
	}
	
	// Check if we can enter the new cover
	if (!CanEnterCover(NewCoverLocation, NewCoverNormal))
	{
		return false;
	}
	
	// Activate the move to adjacent cover ability
	if (ActivateAbilityByTag(MoveToAdjacentCoverTag))
	{
		// Update cover information
		CurrentCoverLocation = NewCoverLocation;
		CurrentCoverNormal = NewCoverNormal;
		
		return true;
	}
	
	return false;
}

void UCoverComponent::GrantCoverAbilities()
{
	if (!OwnerAbilitySystemComponent)
	{
		return;
	}
	
	// Grant the cover abilities to the owner
	if (EnterCoverAbility)
	{
		FGameplayAbilitySpec AbilitySpec(EnterCoverAbility, 1, INDEX_NONE, this);
		OwnerAbilitySystemComponent->GiveAbility(AbilitySpec);
	}
	
	if (ExitCoverAbility)
	{
		FGameplayAbilitySpec AbilitySpec(ExitCoverAbility, 1, INDEX_NONE, this);
		OwnerAbilitySystemComponent->GiveAbility(AbilitySpec);
	}
	
	if (FireFromCoverAbility)
	{
		FGameplayAbilitySpec AbilitySpec(FireFromCoverAbility, 1, INDEX_NONE, this);
		OwnerAbilitySystemComponent->GiveAbility(AbilitySpec);
	}
	
	if (BlindFireAbility)
	{
		FGameplayAbilitySpec AbilitySpec(BlindFireAbility, 1, INDEX_NONE, this);
		OwnerAbilitySystemComponent->GiveAbility(AbilitySpec);
	}
	
	if (MoveToAdjacentCoverAbility)
	{
		FGameplayAbilitySpec AbilitySpec(MoveToAdjacentCoverAbility, 1, INDEX_NONE, this);
		OwnerAbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

bool UCoverComponent::ActivateAbilityByTag(const FGameplayTag& AbilityTag)
{
	if (!OwnerAbilitySystemComponent)
	{
		return false;
	}
	
	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(AbilityTag);
	
	return OwnerAbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);
}

UAbilitySystemComponent* UCoverComponent::GetOwnerAbilitySystemComponent()
{
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return nullptr;
	}
	
	IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(Owner);
	if (!AbilitySystemInterface)
	{
		return nullptr;
	}
	
	return AbilitySystemInterface->GetAbilitySystemComponent();
} 