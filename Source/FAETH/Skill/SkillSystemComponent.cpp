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

void USkillSystemComponent::AddNewSkill(USkill* NewSkill)
{
	if (!NewSkill)
		return;

	if (NewSkill->bUnlocked || NewSkill->bEnabled)
		UE_LOG(LogTemp, Warning, TEXT("Added a new skill that is already unlocked or enabled."));

	Skills.Add(NewSkill);
}

bool USkillSystemComponent::CanUnlockSkill(USkill* Skill)
{
	if (!Skill || Skill->bUnlocked)
		return false;

	if (!Skill->CanPayUnlockCost())
		return false;

	if (!HasMetPrerequisiteConditions(Skill))
		return false;

	if (!Skill->CheckAdditionalUnlockConditions())
		return false;

	return true;
}

bool USkillSystemComponent::HasMetPrerequisiteConditions(USkill* Skill)
{
	if (!Skill)
		return false;

	TArray<FSkillPrerequisiteCondition> PrereqCon = Skill->PrerequisiteConditions;
	TArray<USkill*> UnlockedSkills = GetUnlockedSkills();

	bool bOrConditionSuccess = false;

	for (int i = 0; i < PrereqCon.Num(); ++i)
	{
		if (PrereqCon[i].ConditionType == EConditionType::AND)
		{
			bool bFound = false;

			// Try to determine if the skill has been unlocked.
			for (int j = 0; j < UnlockedSkills.Num(); ++j)
			{
				if (PrereqCon[i].RequiredSkillID == UnlockedSkills[j]->SkillID)
				{
					bFound = true;
					break;
				}
			}

			// If skill is not found, then the condition has failed.
			if (!bFound)
			{
				return false;
			}
		}
		else if (PrereqCon[i].ConditionType == EConditionType::OR)
		{
			// If one OR condition has already succeeded, skip the rest.
			if (bOrConditionSuccess)
				continue;

			// Try to determine if the skill has been unlocked.
			for (int j = 0; j < UnlockedSkills.Num(); ++j)
			{
				if (PrereqCon[i].RequiredSkillID == UnlockedSkills[j]->SkillID)
				{
					// If one is found, set the OR condition to true for this function call.
					bOrConditionSuccess = true;
					break;
				}
			}
		}
		else if (PrereqCon[i].ConditionType == EConditionType::NOT)
		{
			bool bFound = false;

			// Try to determine if the skill has been unlocked.
			for (int j = 0; j < UnlockedSkills.Num(); ++j)
			{
				if (PrereqCon[i].RequiredSkillID == UnlockedSkills[j]->SkillID)
				{
					bFound = true;
					break;
				}
			}

			// If skill is found, then the condition has failed.
			if (bFound)
			{
				return false;
			}
		}
	}

	// We only need to return the result of the OR condition since it is the only condition type that cannot exit early.
	return bOrConditionSuccess;
}

bool USkillSystemComponent::TryUnlockSkill(USkill* Skill, bool bAutoEnable)
{
	if (!Skill || Skill->GetSkillSystemComponent() != this)
		return false;

	if (!CanUnlockSkill(Skill))
		return false;

	if (!Skill->TryPayUnlockCost())
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

	for (int i = 0; i < InitialSkills.Num(); ++i)
	{
		USkill* NewSkill = NewObject<USkill>(this, InitialSkills[i]);
		Skills.Add(NewSkill);
	}
}

void USkillSystemComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);

	// To do: handle the saving of the component data
}
