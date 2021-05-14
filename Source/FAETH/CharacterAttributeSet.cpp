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

void UCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		OnHealthChange.Broadcast(GetHealth(), GetMaxHealth());
	}

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
		OnManaChange.Broadcast(GetMana(), GetMaxMana());
	}

	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
		OnStaminaChange.Broadcast(GetStamina(), GetMaxStamina());
	}
}
