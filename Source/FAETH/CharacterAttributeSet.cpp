#include "CharacterAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

UCharacterAttributeSet::UCharacterAttributeSet()
{
}

void UCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	else if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	}
	else if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxStamina());
	}
}

void UCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayAttribute Attribute = Data.EvaluatedData.Attribute;

	if (Attribute == GetHealthAttribute())
	{
		//SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		OnHealthChange.Broadcast(GetHealth(), GetMaxHealth());
	}
	else if (Attribute == GetManaAttribute())
	{
		//SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
		OnManaChange.Broadcast(GetMana(), GetMaxMana());
	}
	else if (Attribute == GetStaminaAttribute())
	{
		//SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
		OnStaminaChange.Broadcast(GetStamina(), GetMaxStamina());
	}
}

