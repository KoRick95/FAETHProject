#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "FaethObjectTypes.h"
#include "FaethAbility.generated.h"

UCLASS()
class FAETH_API UFaethAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	bool bAutoActivate = false;

	UPROPERTY(EditAnywhere)
	EAbilityInputID AbilityInputID = EAbilityInputID::None;

public:
	UFUNCTION(BlueprintCallable)
	float GetAbilityCost(FString AbilityCostType);

protected:
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};
