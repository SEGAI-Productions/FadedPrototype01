#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FadedCharacter.generated.h"

UCLASS(config = Game)
class AFadedCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFadedCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};


UINTERFACE(Blueprintable, BlueprintType)
class UFadedCharacterInterface : public UInterface {
	GENERATED_BODY()
};

class IFadedCharacterInterface {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "FadedCharacterInterface")
	void TestFunction1();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "FadedCharacterInterface")
	void TestFunction2();
};