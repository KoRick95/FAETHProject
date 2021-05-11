#include "BaseGameplayAbility.h"

float UBaseGameplayAbility::GetAbilityCost(FString AbilityCostType)
{
	float Cost = 0;

	for (FGameplayModifierInfo Modifier : GetCostGameplayEffect()->Modifiers)
	{
		if (Modifier.Attribute.AttributeName == AbilityCostType)
		{
			Modifier.ModifierMagnitude.GetStaticMagnitudeIfPossible(1, Cost);
		}
	}

	return Cost;
}