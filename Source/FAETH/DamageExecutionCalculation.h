#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DamageExecutionCalculation.generated.h"

/**
 * 
 */
UCLASS()
class FAETH_API UDamageExecutionCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UDamageExecutionCalculation();

	void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const;
};
