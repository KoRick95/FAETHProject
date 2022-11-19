#include "SkillSetComponent.h"
#include "../Character/FaethCharacter.h"
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

void USkillSetComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
	
	// To do: perhaps tell the skill manager to handle the saving of this component's information.
}
