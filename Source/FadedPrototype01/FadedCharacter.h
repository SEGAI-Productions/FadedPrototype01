#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "FadedCharacter.generated.h"

UINTERFACE(Blueprintable, BlueprintType)
class UFadedCharacter1Interface : public UInterface {
	GENERATED_BODY()
};

class IFadedCharacter1Interface {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "FadedCharacterInterface")
	void TestFunction1();
};

UCLASS(config = Game)
class AFadedCharacter : public ACharacter, public IAbilitySystemInterface, public IFadedCharacter1Interface {
	GENERATED_BODY()
public:
	AFadedCharacter();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	void TestFunction1_Implementation() override;
};