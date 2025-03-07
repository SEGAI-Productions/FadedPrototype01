#pragma once

#include "CoreMinimal.h"
#include "CoverComponent.h"
#include "CoverSystemInterface.h"
#include "FadedPrototype01/Characters/FadedCharacterBase.h"
#include "FadedCharacterCoverComponent.generated.h"

class AFadedCharacter;

/**
 * Cover component specifically designed for FadedCharacter
 */
UCLASS()
class COVERSYSTEM_API UFadedCharacterCoverComponent : public UCoverComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UFadedCharacterCoverComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// The FadedCharacter owner
	UPROPERTY()
	AFadedCharacterBase* FadedCharacterOwner;
	
	// The input action for entering cover
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* EnterCoverAction;
	
	// The input action for exiting cover
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* ExitCoverAction;
	
	// The input action for firing from cover
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* FireFromCoverAction;
	
	// The input action for blind firing from cover
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* BlindFireAction;
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Setup the input component
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
	
private:
	// Input handlers
	void HandleEnterCoverAction(const struct FInputActionValue& Value);
	void HandleExitCoverAction(const struct FInputActionValue& Value);
	void HandleFireFromCoverAction(const struct FInputActionValue& Value);
	void HandleBlindFireAction(const struct FInputActionValue& Value);
}; 