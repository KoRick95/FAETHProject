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
	Stagger = 0;
	MaxStagger = 5;

	Strength = 0;
	Defence = 0;
	Magic = 0;
	MagicDefence = 0;
}

void UCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UCharacterAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UCharacterAttributeSet, Health)))
	{
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.0f, MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.0f, MaxHealth.GetCurrentValue()));
		OnHealthChange.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());
	}

	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UCharacterAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UCharacterAttributeSet, Mana)))
	{
		Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.0f, MaxMana.GetCurrentValue()));
		Mana.SetBaseValue(FMath::Clamp(Mana.GetCurrentValue(), 0.0f, MaxMana.GetCurrentValue()));
		OnManaChange.Broadcast(Mana.GetCurrentValue(), MaxMana.GetCurrentValue());
	}

	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UCharacterAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UCharacterAttributeSet, Stamina)))
	{
		Stamina.SetCurrentValue(FMath::Clamp(Stamina.GetCurrentValue(), 0.0f, MaxStamina.GetCurrentValue()));
		Stamina.SetBaseValue(FMath::Clamp(Stamina.GetCurrentValue(), 0.0f, MaxStamina.GetCurrentValue()));
		OnStaminaChange.Broadcast(Stamina.GetCurrentValue(), MaxStamina.GetCurrentValue());
	}

	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UCharacterAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UCharacterAttributeSet, Stagger)))
	{
		Stagger.SetCurrentValue(FMath::Clamp(Stagger.GetCurrentValue(), 0.0f, MaxStagger.GetCurrentValue()));
		Stagger.SetBaseValue(FMath::Clamp(Stagger.GetCurrentValue(), 0.0f, MaxStagger.GetCurrentValue()));
		OnStaggerChange.Broadcast(Stagger.GetCurrentValue(), MaxStagger.GetCurrentValue());
	}
}
