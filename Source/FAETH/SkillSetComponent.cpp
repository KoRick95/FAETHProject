#include "SkillSetComponent.h"
#include "FaethCharacter.h"
#include "Skill.h"

USkillSetComponent::USkillSetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

USkill* USkillSetComponent::GetSkillByClass(TSubclassOf<USkill> SkillClass)
{
	for (int i = 0; i < SkillSet.Num(); ++i)
	{
		if (SkillSet[i]->GetClass() == SkillClass)
		{
			return SkillSet[i];
		}
	}

	return nullptr;
}

void USkillSetComponent::ActivateSkill(USkill* Skill)
{
	if (Skill)
	{
		Skill->ActivateSkill();
	}
}

void USkillSetComponent::DeactivateSkill(USkill* Skill)
{
	if (Skill)
	{
		Skill->DeactivateSkill();
	}
}

void USkillSetComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningCharacter = Cast<AFaethCharacter>(GetOwner());
}
