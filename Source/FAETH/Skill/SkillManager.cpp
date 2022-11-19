#include "SkillManager.h"
#include "../Character/FaethCharacter.h"

AFaethCharacter* USkillManager::GetOwningCharacter()
{
	return OwningCharacter;
}

void USkillManager::SetOwningCharacter(AFaethCharacter* NewCharacter)
{
	if (OwningCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set owning character failed: You cannot override skill manager %s's owning character."), *GetName());
		return;
	}

	OwningCharacter = NewCharacter;
}

void USkillManager::BeginPlay()
{
	Super::BeginPlay();

	if (OwningCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Skill manager %s is not assigned to a character."), *GetName());
		return;
	}
}
