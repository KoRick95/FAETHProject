#include "Skill.h"
#include "SkillSystemComponent.h"
#include "../FaethAbility.h"
#include "../Character/CharacterAttributeSet.h"
#include "../Character/PlayableCharacter.h"

USkillSystemComponent* USkill::GetSkillSystemComponent()
{
	return Cast<USkillSystemComponent>(GetOuter());
}

APlayableCharacter* USkill::GetOwningCharacter()
{
	if (!OwningCharacter)
	{
		USkillSystemComponent* SkillSystemComponent = GetSkillSystemComponent();

		if (SkillSystemComponent)
			OwningCharacter = SkillSystemComponent->GetOwningCharacter();
	}

	return OwningCharacter;
}

bool USkill::CanPayUnlockCost_Implementation()
{
	APlayableCharacter* Character = GetOwningCharacter();

	if (!Character)
		return false;

	UCharacterAttributeSet* AttributeSet = Character->GetCharacterAttributeSet();

	if (!AttributeSet)
		return false;

	if (AttributeSet->JobPoints.GetBaseValue() < JobPointsCost)
		return false;

	if (AttributeSet->SkillPoints.GetBaseValue() < SkillPointsCost)
		return false;

	return true;
}

bool USkill::CheckAdditionalUnlockConditions_Implementation()
{
	return true;
}

bool USkill::TryPayUnlockCost_Implementation()
{
	if (!CanPayUnlockCost())
		return false;

	UCharacterAttributeSet* AttributeSet = GetOwningCharacter()->GetCharacterAttributeSet();

	AttributeSet->SetJobPoints(AttributeSet->JobPoints.GetBaseValue() - JobPointsCost);
	AttributeSet->SetSkillPoints(AttributeSet->SkillPoints.GetBaseValue() - SkillPointsCost);

	return true;
}
