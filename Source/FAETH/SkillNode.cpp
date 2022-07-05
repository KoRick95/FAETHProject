#include "SkillNode.h"
#include "SkillNodeLink.h"
#include "FaethCharacter.h"
#include "FaethGameplayAbility.h"

USkillNodeLink* USkillNode::CreateNodeLinkTo(USkillNode* OtherNode)
{
	for (int i = 0; i < NodeLinks.Num(); ++i)
	{
		if (NodeLinks[i]->EndNode == OtherNode)
		{
			UE_LOG(LogTemp, Warning, TEXT("Create node link failed: Node link from %s to %s already exists."), *GetName(), *OtherNode->GetName());
			return nullptr;
		}
	}

	USkillNodeLink* NewLink = NewObject<USkillNodeLink>();
	NewLink->SetNodes(this, OtherNode);
	NodeLinks.Add(NewLink);

	return NewLink;
}

void USkillNode::GiveSkillToCharacter(AFaethCharacter* Character)
{
	// If node is already activated or is not yet unlocked, do nothing.
	if (bIsActivated || !bIsUnlocked)
	{
		return;
	}

	// Give ability to the character.
	if (SkillAbilityClass)
	{
		Character->GainAbility(SkillAbilityClass);
	}

	// Apply gameplay effect to character.
	if (SkillEffectClass)
	{
		// To do: Change the GE level to dynamic.
		Character->AbilitySystemComponent->ApplyGameplayEffectToSelf(NewObject<UGameplayEffect>(SkillEffectClass), 1, Character->AbilitySystemComponent->MakeEffectContext());
	}

	bIsActivated = true;
}

bool USkillNode::CheckUnlockConditions_Implementation()
{
	/* To do: Default implementation */

	return false;
}
