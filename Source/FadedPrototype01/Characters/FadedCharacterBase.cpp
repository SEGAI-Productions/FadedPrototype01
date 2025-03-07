#include "FadedCharacterBase.h"
#include "Components/CapsuleComponent.h"

AFadedCharacterBase::AFadedCharacterBase() {
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -98.0f));
    GetMesh()->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));  //FRotator(Pitch(Y), Yaw(Z), Roll(X))
    static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBP(TEXT("/Game/Blueprints/Characters/Common/ABP_FadedCharacter"));
    if (AnimBP.Succeeded()) { GetMesh()->SetAnimInstanceClass(AnimBP.Class); }
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Characters/Common/Meshes/SKM_Fader"));
    if (MeshAsset.Succeeded()) { GetMesh()->SetSkeletalMesh(MeshAsset.Object); }
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
}

void AFadedCharacterBase::BeginPlay() {
    Super::BeginPlay();
    AbilitySystemComponent->InitAbilityActorInfo(this, this);
    static const FString AbilityPath = TEXT("/Game/Blueprints/Characters/Common/Abilities/GA_Dodge.GA_Dodge_C");
    UClass* AbilityClass = StaticLoadClass(UGameplayAbility::StaticClass(), nullptr, *AbilityPath);
    FGameplayAbilitySpec AbilitySpec(AbilityClass, 1);
    AbilitySystemComponent->GiveAbility(AbilitySpec);
}

UAbilitySystemComponent* AFadedCharacterBase::GetAbilitySystemComponent() const {
    return AbilitySystemComponent;
}

void AFadedCharacterBase::TestFunction1_Implementation() {
    UE_LOG(LogTemp, Warning, TEXT("TestFunction1_Implementation"));
}

bool AFadedCharacterBase::ActivateAbilityByTag(const FGameplayTag& AbilityTag) {
    FGameplayTagContainer TagContainer;
    TagContainer.AddTag(AbilityTag);
    return AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);
}
