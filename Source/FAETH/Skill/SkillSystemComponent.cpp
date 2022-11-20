#include "SkillSystemComponent.h"
#include "Skill.h"
#include "../Character/CharacterAttributeSet.h"
#include "../Character/PlayableCharacter.h"

TArray<USkill*> USkillSystemComponent::GetUnlockedSkills()
{
	TArray<USkill*> UnlockedSkills;

	for (int i = 0; i < Skills.Num(); ++i)
	{
		if (Skills[i]->bUnlocked)
		{
			UnlockedSkills.Add(Skills[i]);
		}
	}

	return UnlockedSkills;
}

USkill* USkillSystemComponent::GetSkillByClass(TSubclassOf<USkill> SkillClass)
{
	for (int i = 0; i < Skills.Num(); ++i)
	{
		if (Skills[i]->GetClass() == SkillClass)
		{
			return Skills[i];
		}
	}

	return nullptr;
}

USkill* USkillSystemComponent::GetSkillByID(FName SkillID)
{
	for (int i = 0; i < Skills.Num(); ++i)
	{
		if (Skills[i]->SkillID == SkillID)
		{
			return Skills[i];
		}
	}

	return nullptr;
}

APlayableCharacter* USkillSystemComponent::GetOwningCharacter()
{
	return GetOwner<APlayableCharacter>();
}

UCharacterAttributeSet* USkillSystemComponent::GetOwningCharacterAttributeSet()
{
	APlayableCharacter* Character = GetOwningCharacter();

	if (Character)
		return Character->GetCharacterAttributeSet();

	return nullptr;
}

bool USkillSystemComponent::CanUnlockSkill(USkill* Skill)
{
	if (!Skill || Skill->bUnlocked)
		return false;

	if (!Skill->CanPayUnlockCost())
		return false;

	if (!HasUnlockedPrerequisiteSkills(Skill))
		return false;

	if (!Skill->CheckAdditionalUnlockConditions())
		return false;

	return true;
}

bool USkillSystemComponent::HasUnlockedPrerequisiteSkills(USkill* Skill)
{
	if (!Skill)
		return false;

	auto PrereqSkills = Skill->PrerequisiteSkills;
	TArray<USkill*> UnlockedSkills = GetUnlockedSkills();

	for (int i = 0; i < PrereqSkills.Num(); ++i)
	{
		bool bFound = false;

		for (int j = 0; j < UnlockedSkills.Num(); ++i)
		{
			if (UnlockedSkills[i]->GetClass() == PrereqSkills[i])
			{
				bFound = true;
				break;
			}
		}

		if (!bFound)
		{
			return false;
		}
	}

	return true;
}

bool USkillSystemComponent::TryUnlockSkill(USkill* Skill, bool bAutoEnable)
{
	if (!Skill || Skill->GetSkillSystemComponent() != this)
		return false;

	if (!CanUnlockSkill(Skill))
		return false;

	if (Skill->TryPayUnlockCost())
		return false;

	Skill->bUnlocked = true;

	if (bAutoEnable)
		EnableSkill(Skill);

	return true;
}

void USkillSystemComponent::EnableSkill(USkill* Skill)
{
	if (!Skill || Skill->GetSkillSystemComponent() != this || !Skill->bUnlocked || Skill->bEnabled)
		return;

	APlayableCharacter* Character = GetOwningCharacter();

	if (Character)
	{
		Character->LearnAbility(Skill->AbilityClass, Character->GetCharacterAttributeSet()->GetLevel());
		Skill->bEnabled = true;
	}
}

void USkillSystemComponent::DisableSkill(USkill* Skill)
{
	if (!Skill || Skill->GetSkillSystemComponent() != this || !Skill->bUnlocked || Skill->bEnabled)
		return;

	APlayableCharacter* Character = GetOwningCharacter();

	if (Character)
	{
		Character->ForgetAbility(Skill->AbilityClass);
		Skill->bEnabled = false;
	}
}

void USkillSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// To do: if can read save data, then initialize from save data

	for (int i = 0; i < SkillSet.Num(); ++i)
	{
		USkill* NewSkill = NewObject<USkill>(this, SkillSet[i]);
		Skills.Add(NewSkill);
	}
}

void USkillSystemComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);

	// To do: handle the saving of the component data
}
