#include "FaethAbility.h"
#include "AbilitySystemComponent.h"

float UFaethAbility::GetAbilityCost(FString AbilityCostType)
{
	float Cost = 0;

	for (FGameplayModifierInfo Modifier : GetCostGameplayEffect()->Modifiers)
	{
		if (Modifier.Attribute.AttributeName == AbilityCostType)
		{
			Modifier.ModifierMagnitude.GetStaticMagnitudeIfPossible(1, Cost);
			break;
		}
	}

	return Cost;
}

void UFaethAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (bAutoActivate)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}
