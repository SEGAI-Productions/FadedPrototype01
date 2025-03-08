#pragma once

#include "CoreMinimal.h"
#include "UObject/UObjectGlobals.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "FadedCharacterEventsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttackDelegate, FGameplayTag, AttackTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeathDelegate, ACharacter*, Character);

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FADEDCORE_API UFadedCharacterEventsComponent : public UActorComponent {
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "FadedCharacterInterface")
    FDeathDelegate OnDeath;
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "FadedCharacterInterface")
    FAttackDelegate OnAttack;
};