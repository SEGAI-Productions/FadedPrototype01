#include "FadedPlayerBase.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameplayTagsManager.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AFadedPlayerBase::AFadedPlayerBase() {
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void AFadedPlayerBase::NotifyControllerChanged() {
    Super::NotifyControllerChanged();
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AFadedPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction  , ETriggerEvent::Triggered, this, &AFadedPlayerBase::Move  );
		EnhancedInputComponent->BindAction(LookAction  , ETriggerEvent::Triggered, this, &AFadedPlayerBase::Look  );
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AFadedPlayerBase::Sprint);
		EnhancedInputComponent->BindAction(DodgeAction , ETriggerEvent::Triggered, this, &AFadedPlayerBase::Dodge );
	}
	else {
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AFadedPlayerBase::Move(const FInputActionValue& Value) {
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AFadedPlayerBase::Look(const FInputActionValue& Value) {
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr) {
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AFadedPlayerBase::Sprint(const FInputActionValue& Value) {
    if (Value.Get<bool>()) {
        GetCharacterMovement()->MaxWalkSpeed = SPRINT_SPEED;
    }
    else {
        GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;
    }
}

void AFadedPlayerBase::Dodge(const FInputActionValue& Value) {
    if (Value.Get<bool>()) {
        FGameplayTag DodgeTag = FGameplayTag::RequestGameplayTag(FName("Faded.Abilities.Movement.Dodge"));
        bool activated = ActivateAbilityByTag(DodgeTag);
		UE_LOG(LogTemp, Warning, TEXT("Dodge activated: %s"), activated ? TEXT("true") : TEXT("false"));
    }
}