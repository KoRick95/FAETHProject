#include "SkillSystemComponent.h"
#include "../Character/FaethCharacter.h"
#include "Skill.h"

USkillSystemComponent::USkillSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

USkill* USkillSystemComponent::GetSkillByClass(TSubclassOf<USkill> SkillClass)
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

void USkillSystemComponent::ActivateSkill(USkill* Skill)
{
	if (Skill)
	{
		Skill->ActivateSkill();
	}
}

void USkillSystemComponent::DeactivateSkill(USkill* Skill)
{
	if (Skill)
	{
		Skill->DeactivateSkill();
	}
}

void USkillSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningCharacter = Cast<AFaethCharacter>(GetOwner());
}

void USkillSystemComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
	
	// To do: perhaps tell the skill manager to handle the saving of this component's information.
}
