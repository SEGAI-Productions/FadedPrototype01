#include "FadedCharacter.h"
#include "Components/CapsuleComponent.h"

AFadedCharacter::AFadedCharacter() {
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -98.0f));
    GetMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f,270.0f));
    static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBP(TEXT("/Game/Blueprints/Characters/Common/ABP_FadedCharacter"));
    if (AnimBP.Succeeded()) { GetMesh()->SetAnimInstanceClass(AnimBP.Class); }
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Characters/Common/Meshes/SKM_Fader"));
    if (MeshAsset.Succeeded()) { GetMesh()->SetSkeletalMesh(MeshAsset.Object); }
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
}
UAbilitySystemComponent* AFadedCharacter::GetAbilitySystemComponent() const {
    return AbilitySystemComponent;
}
void AFadedCharacter::TestFunction1_Implementation() {
    UE_LOG(LogTemp, Warning, TEXT("TestFunction1_Implementation"));
}
