#include "Skill.h"
#include "FaethCharacter.h"
#include "FaethAbility.h"
#include "SkillSetComponent.h"

AFaethCharacter* USkill::GetOwningCharacter()
{
	if (OwningComponent)
		return OwningComponent->OwningCharacter;

	return nullptr;
}

void USkill::ActivateSkill()
{
	// If the skill is not yet unlocked, or is already activated, then do nothing.
	if (!bUnlocked || bActivated)
	{
		return;
	}

	ApplySkillTo(GetOwningCharacter());

	bActivated = true;
}

void USkill::DeactivateSkill()
{
	// If the skill is not already activated, then do nothing.
	if (!bActivated)
	{
		return;
	}

	RemoveSkillFrom(GetOwningCharacter());

	bActivated = false;
}

void USkill::ApplySkillTo(AFaethCharacter* Character)
{
	// If the skill is already applied, then do nothing.
	if (!Character || bApplied)
	{
		return;
	}

	// Give the ability to the character.
	if (SkillAbilityClass)
	{
		Character->GainAbility(SkillAbilityClass);
	}

	// Apply the effect to the character.
	if (SkillEffectClass)
	{
		Character->GainEffect(SkillEffectClass);
	}

	bApplied = true;
}

void USkill::RemoveSkillFrom(AFaethCharacter* Character)
{
	// If the skill hasn't been applied, then do nothing.
	if (!Character || !bApplied)
	{
		return;
	}

	// Remove the ability from the character.
	if (SkillAbilityClass)
	{
		Character->LoseAbility(SkillAbilityClass);
	}
	
	// Remove the effect from the character.
	if (SkillEffectClass)
	{
		Character->LoseEffect(SkillEffectClass);
	}

	bApplied = false;
}

void USkill::BeginPlay()
{
	OwningComponent = Cast<USkillSetComponent>(GetOuter());

	if (!OwningComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Skill %s does not have a valid SkillSetComponent outer."), *GetName());
		return;
	}

	// If the skill is activated before runtime, then apply the skill.
	if (IsActivated())
	{
		ApplySkillTo(GetOwningCharacter());
	}

	Super::BeginPlay();
}
