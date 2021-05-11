#pragma once

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EquipmentAttributeSet.generated.h"

UCLASS()
class FAETH_API UEquipmentAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UEquipmentAttributeSet() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UEquipmentAttributeSet, Health);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UEquipmentAttributeSet, Mana);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UEquipmentAttributeSet, Stamina);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UEquipmentAttributeSet, Strength);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UEquipmentAttributeSet, Dexterity);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UEquipmentAttributeSet, Intelligence);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Agility;
	ATTRIBUTE_ACCESSORS(UEquipmentAttributeSet, Agility);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Armour;
	ATTRIBUTE_ACCESSORS(UEquipmentAttributeSet, Armour);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Resistance;
	ATTRIBUTE_ACCESSORS(UEquipmentAttributeSet, Resistance);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData PhysicalAttack;
	ATTRIBUTE_ACCESSORS(UEquipmentAttributeSet, PhysicalAttack);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData MagicAttack;
	ATTRIBUTE_ACCESSORS(UEquipmentAttributeSet, MagicAttack);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UEquipmentAttributeSet, AttackSpeed);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData HealthRegen;
	ATTRIBUTE_ACCESSORS(UEquipmentAttributeSet, HealthRegen);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData ManaRegen;
	ATTRIBUTE_ACCESSORS(UEquipmentAttributeSet, ManaRegen);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData StaminaRegen;
	ATTRIBUTE_ACCESSORS(UEquipmentAttributeSet, StaminaRegen);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData StaggerChance;
	ATTRIBUTE_ACCESSORS(UEquipmentAttributeSet, StaggerChance);
};
