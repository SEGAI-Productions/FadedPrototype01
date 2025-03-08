#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "FadedCore/Public/Interfaces/FadedCharacterInterface.h"
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
	
	// Ability class that can be set in the editor
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TSubclassOf<UGameplayAbility> DodgeAbilityClass;
	
	// Array of default abilities to grant
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;
public:	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	void TestFunction1_Implementation() override;
	
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool ActivateAbilityByTag(const FGameplayTag& AbilityTag);
};