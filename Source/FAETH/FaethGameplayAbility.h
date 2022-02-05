#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "FaethGameplayAbility.generated.h"

UCLASS()
class FAETH_API UFaethGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	float GetAbilityCost(FString AbilityCostType);
};
