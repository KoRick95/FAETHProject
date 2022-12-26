#include "SkillSystemComponent.h"
#include "Skill.h"
#include "../Character/CharacterAttributeSet.h"
#include "../Character/PlayableCharacter.h"
#include "../FAETH.h"

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

	// Log a warning if the skill is already unlocked or enabled, as those states shouldn't be changed externally.
	if (NewSkill->bUnlocked || NewSkill->bEnabled)
	{
		UE_LOG(FaethLog, Warning, TEXT("Adding a new skill %s that is already unlocked or enabled."), *NewSkill->SkillID.ToString());
	}

	// If the outer of the given skill is not this, then change it to this.
	if (NewSkill->GetOuter() != this && NewSkill->Rename(*NewSkill->SkillID.ToString(), this))
	{
		UE_LOG(FaethLog, Warning, TEXT("Cannot change the outer of skill %s to this component."), *NewSkill->SkillID.ToString());
	}

	Skills.Add(NewSkill);
}

bool USkillSystemComponent::CanUnlockSkill(USkill* Skill)
{
	if (!Skill)
		return false;

	if (Skill->bUnlocked)
	{
		UE_LOG(FaethLog, Display, TEXT("Skill %s is already unlocked."), *Skill->SkillID.ToString());
		return false;
	}

	if (!Skill->CanPayUnlockCost())
	{
		UE_LOG(FaethLog, Display, TEXT("The unlock cost of skill %s cannot be paid."), *Skill->SkillID.ToString());
		return false;
	}

	if (!HasMetPrerequisiteConditions(Skill))
	{
		UE_LOG(FaethLog, Display, TEXT("The prerequisite conditions of skill %s has not been met."), *Skill->SkillID.ToString());
		return false;
	}

	if (!Skill->CheckAdditionalUnlockConditions())
	{
		UE_LOG(FaethLog, Display, TEXT("The additional unlock conditions of skill %s has not been met."), *Skill->SkillID.ToString());
		return false;
	}

	return true;
}

bool USkillSystemComponent::HasMetPrerequisiteConditions(USkill* Skill)
{
	if (!Skill)
		return false;

	// Get the skill's prerequite conditions array.
	TArray<FSkillPrerequisiteCondition> PrereqCons = Skill->PrerequisiteConditions;

	// If there are no prerequisite conditions, then just return true.
	if (PrereqCons.IsEmpty())
		return true;

	TArray<USkill*> UnlockedSkills = GetUnlockedSkills();

	bool bUsesOrCondition = false; // If it doesn't have any OR condition, ignore bOrConditionSuccess.
	bool bOrConditionSuccess = false; // Whether any of the OR conditions succeeds in the entire array.

	for (int i = 0; i < PrereqCons.Num(); ++i)
	{
		if (PrereqCons[i].ConditionType == EConditionType::AND)
		{
			bool bFound = false;

			// Try to determine if the skill has been unlocked.
			for (int j = 0; j < UnlockedSkills.Num(); ++j)
			{
				if (PrereqCons[i].RequiredSkillID == UnlockedSkills[j]->SkillID)
				{
					bFound = true;
					break;
				}
			}

			if (!bFound)
			{
				UE_LOG(FaethLog, Display, TEXT("AND requirement of skill %s to unlock the skill %s has not been met."),
					*PrereqCons[i].RequiredSkillID.ToString(), *Skill->SkillID.ToString());
				return false;
			}
		}
		else if (PrereqCons[i].ConditionType == EConditionType::OR)
		{
			bUsesOrCondition = true;

			// If one OR condition has already succeeded, skip the rest.
			if (bOrConditionSuccess)
				continue;

			// Try to determine if the skill has been unlocked.
			for (int j = 0; j < UnlockedSkills.Num(); ++j)
			{
				if (PrereqCons[i].RequiredSkillID == UnlockedSkills[j]->SkillID)
				{
					// If one is found, set the OR condition to true for this function call.
					bOrConditionSuccess = true;
					break;
				}
			}
		}
		else if (PrereqCons[i].ConditionType == EConditionType::NOT)
		{
			bool bFound = false;

			// Try to determine if the skill has been unlocked.
			for (int j = 0; j < UnlockedSkills.Num(); ++j)
			{
				if (PrereqCons[i].RequiredSkillID == UnlockedSkills[j]->SkillID)
				{
					bFound = true;
					break;
				}
			}

			if (bFound)
			{
				UE_LOG(FaethLog, Display, TEXT("NOT requirement of skill %s to unlock the skill %s has not been met."),
					*PrereqCons[i].RequiredSkillID.ToString(), *Skill->SkillID.ToString());
				return false;
			}
		}
	}

	// If any OR conditions were checked, then...
	// We need to return the result since it is the only condition type that cannot exit early.
	if (bUsesOrCondition)
	{
		UE_LOG(FaethLog, Display, TEXT("None of the OR requirements to unlock skill %s were met."), *Skill->SkillID.ToString());
		return bOrConditionSuccess;
	}

	// Otherwise it has passed every condition.
	return true;
}

bool USkillSystemComponent::TryUnlockSkill(USkill* Skill, bool bAutoEnable)
{
	if (!Skill || Skill->GetSkillSystemComponent() != this)
	{
		UE_LOG(FaethLog, Warning, TEXT("Attempted to unlock an invalid skill."));
		return false;
	}

	if (!CanUnlockSkill(Skill))
	{
		UE_LOG(FaethLog, Display, TEXT("Attempted to unlock the skill %s but it cannot yet be unlocked."), *Skill->SkillID.ToString());
		return false;
	}
	
	if (!Skill->TryPayUnlockCost())
	{
		UE_LOG(FaethLog, Warning, TEXT("Attempted to pay the unlock cost of skill %s and failed."), *Skill->SkillID.ToString());
		return false;
	}

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
		AddNewSkill(NewSkill);
	}
}

void USkillSystemComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);

	// To do: handle the saving of the component data
}
