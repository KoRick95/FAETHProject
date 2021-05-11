#pragma once

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CharacterAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangeDelegate, float, Health, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnManaChangeDelegate, float, Mana, float, MaxMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChangeDelegate, float, Stamina, float, MaxStamina);

UCLASS()
class FAETH_API UCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UCharacterAttributeSet();

	FOnHealthChangeDelegate OnHealthChange;
	FOnManaChangeDelegate OnManaChange;
	FOnStaminaChangeDelegate OnStaminaChange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Health);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxHealth);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Mana);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxMana);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Stamina);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxStamina);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Stagger;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Stagger);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData MaxStagger;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxStagger);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Strength);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Defence;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Defence);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Magic;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Magic);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData MagicDefence;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MagicDefence);

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
