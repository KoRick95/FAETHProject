#include "SkillManager.h"
#include "FaethCharacter.h"

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

USkillNode* USkillManager::SelectNodeByIndex(int ArrayIndex)
{
	if (ArrayIndex >= 0 && ArrayIndex < SkillNodes.Num())
	{
		NodeSelector.Index = ArrayIndex;
		NodeSelector.Node = SkillNodes[ArrayIndex];
		return NodeSelector.Node;
	}
	else if (ArrayIndex == -1)
	{
		return SelectNodeEnd();
	}
	else if (ArrayIndex == SkillNodes.Num())
	{
		return SelectNodeStart();
	}

	return nullptr;
}

USkillNode* USkillManager::SelectNodePrev()
{
	return SelectNodeByIndex(NodeSelector.Index - 1);
}

USkillNode* USkillManager::SelectNodeNext()
{
	return SelectNodeByIndex(NodeSelector.Index + 1);
}

USkillNode* USkillManager::SelectNodeStart()
{
	// To do: Function.
	return nullptr;
}

USkillNode* USkillManager::SelectNodeEnd()
{
	// To do: Function.
	return nullptr;
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

