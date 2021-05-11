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
	UEquipmentAttributeSet();

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
	FGameplayAttributeData Stagger;
	ATTRIBUTE_ACCESSORS(UEquipmentAttributeSet, Stagger);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UEquipmentAttributeSet, Strength);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Defence;
	ATTRIBUTE_ACCESSORS(UEquipmentAttributeSet, Defence);
};
