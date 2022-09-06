#include "FaethAbilitySystemComponent.h"
#include "Skill.h"

USkill* UFaethAbilitySystemComponent::GetSkillByClass(TSubclassOf<USkill> SkillClass)
{
	if (SkillClass)
	{
		for (int i = 0; i < UnlockableSkills.Num(); ++i)
		{
			if (UnlockableSkills[i]->GetClass() == SkillClass)
			{
				return UnlockableSkills[i];
			}
		}
	}

	return nullptr;
}

bool UFaethAbilitySystemComponent::UnlockSkill(USkill* Skill)
{
	if (!Skill || !UnlockableSkills.Contains(Skill))
		return false;

	// To do: check for can pay skill cost, then pay unlock skill cost

	Skill->bUnlocked = true;

	return true;
}

bool UFaethAbilitySystemComponent::ActivateSkill(USkill* Skill)
{
	if (!Skill || !UnlockableSkills.Contains(Skill))
		return false;

	

	return false;
}
