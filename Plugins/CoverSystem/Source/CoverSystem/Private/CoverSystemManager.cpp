#include "CoverSystemManager.h"
#include "CoverComponent.h"
#include "GameplayTagsManager.h"
#include "Engine/World.h"

// Initialize the static instance
UCoverSystemManager* UCoverSystemManager::Instance = nullptr;

UCoverSystemManager::UCoverSystemManager()
{
	// Constructor
}

void UCoverSystemManager::Initialize()
{
	// Register gameplay tags
	RegisterGameplayTags();
}

UCoverSystemManager* UCoverSystemManager::GetInstance(UObject* WorldContextObject)
{
	// If the instance doesn't exist, create it
	if (!Instance)
	{
		Instance = NewObject<UCoverSystemManager>(GetTransientPackage(), UCoverSystemManager::StaticClass());
		Instance->Initialize();
	}
	
	return Instance;
}

void UCoverSystemManager::RegisterCoverComponent(UCoverComponent* CoverComponent)
{
	if (!CoverComponent)
	{
		return;
	}
	
	// Add the cover component to the list if it's not already there
	if (!RegisteredCoverComponents.Contains(CoverComponent))
	{
		RegisteredCoverComponents.Add(CoverComponent);
	}
}

void UCoverSystemManager::UnregisterCoverComponent(UCoverComponent* CoverComponent)
{
	if (!CoverComponent)
	{
		return;
	}
	
	// Remove the cover component from the list
	RegisteredCoverComponents.Remove(CoverComponent);
}

TArray<UCoverComponent*> UCoverSystemManager::GetAllCoverComponents() const
{
	return RegisteredCoverComponents;
}

TArray<UCoverComponent*> UCoverSystemManager::GetCoverComponentsInRange(const FVector& Location, float Range) const
{
	TArray<UCoverComponent*> ComponentsInRange;
	
	// Check each registered cover component
	for (UCoverComponent* CoverComponent : RegisteredCoverComponents)
	{
		if (!CoverComponent || !CoverComponent->GetOwner())
		{
			continue;
		}
		
		// Get the distance to the cover component
		float Distance = FVector::Distance(Location, CoverComponent->GetOwner()->GetActorLocation());
		
		// If the distance is within range, add it to the list
		if (Distance <= Range)
		{
			ComponentsInRange.Add(CoverComponent);
		}
	}
	
	return ComponentsInRange;
}

void UCoverSystemManager::RegisterGameplayTags()
{
	// Get the gameplay tags manager
	UGameplayTagsManager& TagsManager = UGameplayTagsManager::Get();
	
	// Register the cover system tags
	TagsManager.AddNativeGameplayTag(FName("Ability.Cover.Enter"));
	TagsManager.AddNativeGameplayTag(FName("Ability.Cover.Exit"));
	TagsManager.AddNativeGameplayTag(FName("Ability.Cover.Fire"));
	TagsManager.AddNativeGameplayTag(FName("Ability.Cover.BlindFire"));
	TagsManager.AddNativeGameplayTag(FName("Ability.Cover.MoveToAdjacent"));
	
	TagsManager.AddNativeGameplayTag(FName("State.Cover.InCover"));
	TagsManager.AddNativeGameplayTag(FName("State.Cover.Entering"));
	TagsManager.AddNativeGameplayTag(FName("State.Cover.Exiting"));
	TagsManager.AddNativeGameplayTag(FName("State.Cover.Firing"));
	TagsManager.AddNativeGameplayTag(FName("State.Cover.BlindFiring"));
	TagsManager.AddNativeGameplayTag(FName("State.Cover.MovingToAdjacent"));
} 