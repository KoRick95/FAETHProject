#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "EquipmentAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class FAETH_API UEquipmentAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UEquipmentAttributeSet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Stagger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Defence;
};
