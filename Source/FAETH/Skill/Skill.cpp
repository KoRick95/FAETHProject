#include "Skill.h"
#include "SkillSetComponent.h"
#include "../FaethAbility.h"
#include "../Character/FaethCharacter.h"

AFaethCharacter* USkill::GetOwningCharacter()
{
	return nullptr;
}

void USkill::ActivateSkill()
{
	// If the skill is not yet unlocked, or is already activated, then do nothing.
	if (!bUnlocked || bEnabled)
	{
		return;
	}

	//ApplySkillTo(GetOwningCharacter());

	bEnabled = true;
}

void USkill::DeactivateSkill()
{
	// If the skill is not already activated, then do nothing.
	if (!bEnabled)
	{
		return;
	}

	//RemoveSkillFrom(GetOwningCharacter());

	bEnabled = false;
}

void USkill::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	// If set to auto activate on granted
	if (bAutoActivate)
	{
		// Try activate the ability on the character
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}

//void USkill::BeginPlay()
//{
//	OwningComponent = Cast<USkillSetComponent>(GetOuter());
//
//	if (!OwningComponent)
//	{
//		UE_LOG(LogTemp, Error, TEXT("Skill %s does not have a valid SkillSetComponent outer."), *GetName());
//		return;
//	}
//
//	// If the skill is activated before runtime, then apply the skill.
//	if (IsActivated())
//	{
//		ApplySkillTo(GetOwningCharacter());
//	}
//
//	Super::BeginPlay();
//}
