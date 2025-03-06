#include "FadedCharacter.h"

AFadedCharacter::AFadedCharacter() {
	PrimaryActorTick.bCanEverTick = true;
}
void AFadedCharacter::BeginPlay() {
	Super::BeginPlay();
}
void AFadedCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}
void AFadedCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
UAbilitySystemComponent* AFadedCharacter::GetAbilitySystemComponent() const {
    return nullptr;
}
void AFadedCharacter::TestFunction1_Implementation() {
    UE_LOG(LogTemp, Warning, TEXT("TestFunction1_Implementation"));
}
