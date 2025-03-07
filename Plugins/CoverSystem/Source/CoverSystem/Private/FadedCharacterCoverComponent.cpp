#include "FadedCharacterCoverComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

UFadedCharacterCoverComponent::UFadedCharacterCoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame
	PrimaryComponentTick.bCanEverTick = true;
}

void UFadedCharacterCoverComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Get the FadedCharacter owner
	FadedCharacterOwner = Cast<AFadedCharacter>(GetOwner());
}

void UFadedCharacterCoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UFadedCharacterCoverComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Cast to enhanced input component
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EnhancedInputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("UFadedCharacterCoverComponent::SetupPlayerInputComponent: Failed to cast to UEnhancedInputComponent"));
		return;
	}
	
	// Bind the input actions
	if (EnterCoverAction)
	{
		EnhancedInputComponent->BindAction(EnterCoverAction, ETriggerEvent::Triggered, this, &UFadedCharacterCoverComponent::HandleEnterCoverAction);
	}
	
	if (ExitCoverAction)
	{
		EnhancedInputComponent->BindAction(ExitCoverAction, ETriggerEvent::Triggered, this, &UFadedCharacterCoverComponent::HandleExitCoverAction);
	}
	
	if (FireFromCoverAction)
	{
		EnhancedInputComponent->BindAction(FireFromCoverAction, ETriggerEvent::Triggered, this, &UFadedCharacterCoverComponent::HandleFireFromCoverAction);
	}
	
	if (BlindFireAction)
	{
		EnhancedInputComponent->BindAction(BlindFireAction, ETriggerEvent::Triggered, this, &UFadedCharacterCoverComponent::HandleBlindFireAction);
	}
}

void UFadedCharacterCoverComponent::HandleEnterCoverAction(const FInputActionValue& Value)
{
	if (!FadedCharacterOwner)
	{
		return;
	}
	
	// Only process if the value is true
	if (!Value.Get<bool>())
	{
		return;
	}
	
	// Find cover nearby
	FVector CoverLocation;
	FVector CoverNormal;
	if (FindCoverNearby(CoverLocation, CoverNormal))
	{
		// Enter cover
		EnterCover(CoverLocation, CoverNormal);
	}
}

void UFadedCharacterCoverComponent::HandleExitCoverAction(const FInputActionValue& Value)
{
	if (!FadedCharacterOwner)
	{
		return;
	}
	
	// Only process if the value is true
	if (!Value.Get<bool>())
	{
		return;
	}
	
	// Exit cover
	if (IsInCover())
	{
		ExitCover();
	}
}

void UFadedCharacterCoverComponent::HandleFireFromCoverAction(const FInputActionValue& Value)
{
	if (!FadedCharacterOwner)
	{
		return;
	}
	
	// Only process if the value is true
	if (!Value.Get<bool>())
	{
		return;
	}
	
	// Fire from cover
	if (IsInCover())
	{
		FireFromCover();
	}
}

void UFadedCharacterCoverComponent::HandleBlindFireAction(const FInputActionValue& Value)
{
	if (!FadedCharacterOwner)
	{
		return;
	}
	
	// Only process if the value is true
	if (!Value.Get<bool>())
	{
		return;
	}
	
	// Blind fire from cover
	if (IsInCover())
	{
		BlindFireFromCover();
	}
} 