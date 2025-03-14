// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CooldownSubsystem.generated.h"

FADEDCORE_API DECLARE_LOG_CATEGORY_EXTERN(LogCooldown, Log, All);

USTRUCT()
struct FCooldownEntry
{
  GENERATED_USTRUCT_BODY()

public:
  UPROPERTY(VisibleAnywhere)
  TSubclassOf<class UObject> CooldownClass;

  UPROPERTY(VisibleAnywhere)
  TWeakObjectPtr<AActor> CooldownOwner;

  UPROPERTY(VisibleAnywhere)
  float CooldownDuration = 0;

  UPROPERTY(VisibleAnywhere)
  float GameTimeSecondsWhenApplied = 0;

  UPROPERTY(VisibleAnywhere)
  float GameTimeSecondsWhenComplete = 0;
};

USTRUCT()
struct FCooldownEntryContainer
{
  GENERATED_USTRUCT_BODY()
public:
  UPROPERTY(VisibleAnywhere)
  TMap<TSubclassOf<class UObject>, FCooldownEntry> CooldownList;
};

/**
 * This class is responsible for tracking actor/global ability cooldowns 
 */
UCLASS()
class FADEDCORE_API UCooldownSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
  // Begin USubsystem
  virtual void Initialize(FSubsystemCollectionBase& Collection) override;
  virtual void Deinitialize() override;
  // End USubsystem

  void ApplyCooldown(TSubclassOf<class UObject> CooldownClass, AActor* CooldownOwner, float CooldownLength);
  void ApplyGlobalCooldown(TSubclassOf<class UObject> CooldownClass, AActor* CooldownOwner, float CooldownLength);
  bool IsOnCooldown(TSubclassOf<class UObject> CooldownClass, AActor* CooldownOwner);
  void GetCooldownTimeRemainingAndDuration(TSubclassOf<class UObject> CooldownClass, AActor* CooldownOwner, float& TimeRemaining, float& CooldownDuration);

  // This could be called by anything (probably GameMode)
  UFUNCTION(BlueprintCallable)
  void PruneOutdatedCooldowns();

  // Set this to true if you don't want to manage manually pruning cooldowns
  UPROPERTY(BlueprintReadWrite, EditAnywhere)
  bool bPruneOnEachApply = false;

protected:
  UPROPERTY(VisibleAnywhere)
  TMap<TSubclassOf<class UObject>, FCooldownEntry> GlobalCooldowns;

  UPROPERTY(VisibleAnywhere)
  TMap<TWeakObjectPtr<AActor>, FCooldownEntryContainer> PerActorCooldowns;

private:
  TSet<TSubclassOf<UObject>> GlobalKeys;
  TSet<TWeakObjectPtr<AActor>> ActorKeys;
  TSet<TSubclassOf<UObject>> ActorCooldownKeys;
};
