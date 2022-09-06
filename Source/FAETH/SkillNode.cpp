#include "SkillNode.h"
#include "SkillManager.h"
#include "FaethCharacter.h"
#include "FaethAbility.h"

AFaethCharacter* USkillNode::GetOwningCharacter()
{
	return SkillManager->GetOwningCharacter();
}

USkillManager* USkillNode::GetSkillManager()
{
	return SkillManager;
}

void USkillNode::SetSkillManager(USkillManager* NewSkillManager)
{
	if (SkillManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set new skill manager failed: You cannot override skill node %s's existing manager."), *GetName());
		return;
	}

	SkillManager = NewSkillManager;
}

void USkillNode::GiveSkillToCharacter(AFaethCharacter* Character)
{
	// If node is already activated or is not yet unlocked, do nothing.
	if (bIsActivated || !bIsUnlocked)
	{
		return;
	}

	// If the passed in character is not valid...
	if (!Character)
	{
		// Use the owning character.
		Character = GetOwningCharacter();

		// If the owning character is also not valid, then do nothing.
		if (!Character)
			return;
	}

	// Give ability to the character.
	if (SkillAbilityClass)
	{
		Character->GainAbility(SkillAbilityClass);
	}

	// Apply gameplay effect to character.
	if (SkillEffectClass)
	{
		// To do: Change the GE level to dynamic.
		Character->AbilitySystemComponent->ApplyGameplayEffectToSelf(NewObject<UGameplayEffect>(SkillEffectClass), 1, Character->AbilitySystemComponent->MakeEffectContext());
	}

	bIsActivated = true;
}

void USkillNode::RemoveSkillFromCharacter(AFaethCharacter* Character)
{
	// If node is not yet activated or unlocked, do nothing.
	if (!bIsActivated || !bIsUnlocked)
	{
		return;
	}

	// If the passed in character is not valid...
	if (!Character)
	{
		// Use the owning character.
		Character = GetOwningCharacter();

		// If the owning character is also not valid, then do nothing.
		if (!Character)
			return;
	}

	if (SkillAbilityClass)
	{
		// To do: Remove ability.
	}

	if (SkillEffectClass)
	{
		// To do: Remove effect.
	}
}

bool USkillNode::CheckUnlockConditions_Implementation()
{
	if (!GetOwningCharacter())
		return false;

	UCharacterAttributeSet* CharacterAttributeSet = GetOwningCharacter()->CharacterAttributeSet;

	if (CharacterAttributeSet->GetJobPoints() >= JobPointsCost &&
		CharacterAttributeSet->GetSkillPoints() >= SkillPointsCost)
		return true;

	return false;
}

void USkillNode::BeginPlay()
{
	Super::BeginPlay();

	if (SkillManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Skill node %s is not assigned to a skill manager."), *GetName());
		return;
	}
}
