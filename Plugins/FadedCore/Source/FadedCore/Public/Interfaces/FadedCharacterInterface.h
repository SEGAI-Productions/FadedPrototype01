#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FadedCharacterInterface.generated.h"

UINTERFACE(Blueprintable, BlueprintType)
class FADEDCORE_API UFadedCharacterInterface : public UInterface {
    GENERATED_BODY()
};

class FADEDCORE_API IFadedCharacterInterface {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "FadedCharacterInterface")
    bool GetIsDead();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "FadedCharacterInterface")
    UFadedCharacterEventsComponent* GetEvents();
};