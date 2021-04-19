#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "CharacterAttributeSet.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangeDelegate, float, Health, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnManaChangeDelegate, float, Mana, float, MaxMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChangeDelegate, float, Stamina, float, MaxStamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaggerChangeDelegate, float, Stagger, float, MaxStagger);

UCLASS()
class FAETH_API UCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UCharacterAttributeSet();

	FOnHealthChangeDelegate OnHealthChange;
	FOnManaChangeDelegate OnManaChange;
	FOnStaminaChangeDelegate OnStaminaChange;
	FOnStaggerChangeDelegate OnStaggerChange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData MaxMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Stagger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData MaxStagger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Magic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData MagicDefense;

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
