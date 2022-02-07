#include "CharacterAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

UCharacterAttributeSet::UCharacterAttributeSet()
{
	MaxHealth = 100;
	Health = MaxHealth;
	MaxMana = 100;
	Mana = MaxMana;
	MaxStamina = 100;
	Stamina = MaxStamina;
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
		NewValue = FMath::Clamp(GetMana(), 0.0f, GetMaxMana());
	}
	else if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina());
	}
}

void UCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		OnHealthChange.Broadcast(GetHealth(), GetMaxHealth());
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		OnManaChange.Broadcast(GetMana(), GetMaxMana());
	}
	else if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		OnStaminaChange.Broadcast(GetStamina(), GetMaxStamina());
	}
}

void UCharacterAttributeSet::InitAttribute(ECharacterAttributeType AttributeType, float InitValue)
{
	switch (AttributeType)
	{
	case ECharacterAttributeType::Health:
		InitHealth(InitValue);
		break;

	case ECharacterAttributeType::MaxHealth:
		InitMaxHealth(InitValue);
		break;

	case ECharacterAttributeType::Mana:
		InitMaxMana(InitValue);
		break;

	case ECharacterAttributeType::MaxMana:
		InitMaxMana(InitValue);
		break;
	}
}
