#include "CharacterAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

UCharacterAttributeSet::UCharacterAttributeSet()
{
}

void UCharacterAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& Attribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AttributeProperty)
{
	UAbilitySystemComponent* asc = GetOwningAbilitySystemComponent();
	float currentMaxValue = MaxAttribute.GetCurrentValue();

	if (asc && !FMath::IsNearlyEqual(currentMaxValue, NewMaxValue))
	{
		float currentValue = Attribute.GetCurrentValue();
		
		// Calculate the percentage difference of the max value, then calculate a delta based off that percentage
		float delta = (currentMaxValue > 0) ? (currentValue / currentMaxValue * NewMaxValue) - currentValue : NewMaxValue;

		// Apply the delta additively to the attribute
		asc->ApplyModToAttributeUnsafe(AttributeProperty, EGameplayModOp::Additive, delta);
	}
}

void UCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
	else if (Attribute == GetMaxManaAttribute())
	{
		AdjustAttributeForMaxChange(Mana, MaxMana, NewValue, GetManaAttribute());
	}
	else if (Attribute == GetMaxStaminaAttribute())
	{
		AdjustAttributeForMaxChange(Stamina, MaxStamina, NewValue, GetStaminaAttribute());
	}
}

void UCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayAttribute attribute = Data.EvaluatedData.Attribute;

	if (attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		OnHealthChange.Broadcast(GetHealth(), GetMaxHealth());
	}
	else if (attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
		OnManaChange.Broadcast(GetMana(), GetMaxMana());
	}
	else if (attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
		OnStaminaChange.Broadcast(GetStamina(), GetMaxStamina());
	}
}

