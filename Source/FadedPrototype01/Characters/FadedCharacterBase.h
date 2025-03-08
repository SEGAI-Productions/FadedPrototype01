#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "FadedCore/Public/Interfaces/FadedCharacterInterface.h"
#include "FadedCore/Public/Components/FadedCharacterEventsComponent.h"
#include "FadedCharacterBase.generated.h"

UCLASS(config = Game)
class FADEDPROTOTYPE01_API AFadedCharacterBase : public ACharacter, public IAbilitySystemInterface, public IFadedCharacterInterface {
	GENERATED_BODY()
public:
	AFadedCharacterBase();
protected:
    virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PoCharacterInterface")
	TObjectPtr<UFadedCharacterEventsComponent> Events;
public:	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UFadedCharacterEventsComponent* GetEvents_Implementation() override;
	
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool ActivateAbilityByTag(const FGameplayTag& AbilityTag);
};