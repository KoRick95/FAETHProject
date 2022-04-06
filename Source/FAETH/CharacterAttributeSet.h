#pragma once

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "FaethObjectTypes.h"
#include "CharacterAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChangeDelegate, float, Attribute, float, MaxAttribute);

UCLASS()
class FAETH_API UCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UCharacterAttributeSet();

	FOnAttributeChangeDelegate OnHealthChange;
	FOnAttributeChangeDelegate OnManaChange;
	FOnAttributeChangeDelegate OnStaminaChange;

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Health);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Mana);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxMana);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Stamina);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxStamina);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData Stagger;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Stagger);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData MaxStagger;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxStagger);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Strength);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Dexterity);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Intelligence);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData Agility;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Agility);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData Defence;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Defence);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData Resistance;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Resistance);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData PhysicalAttack;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, PhysicalAttack);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData MagicAttack;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MagicAttack);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, AttackSpeed);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData HealthRegen;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, HealthRegen);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData ManaRegen;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, ManaRegen);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData StaminaRegen;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, StaminaRegen);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData StaggerPower;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, StaggerPower);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Level);

	UPROPERTY(BlueprintReadWrite)
	FGameplayAttributeData Experience;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Experience);

public:
	void AdjustAttributeForMaxChange(FGameplayAttributeData& Attribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AttributeProperty);

protected:
	void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
