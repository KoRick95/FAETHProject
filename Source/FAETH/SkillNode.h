#pragma once

#include "CoreMinimal.h"
#include "FaethObjectBase.h"
#include "SkillNode.generated.h"

class UFaethGameplayAbility;
class UGameplayEffect;
class USkillNodeLink;
class AFaethCharacter;

UCLASS()
class FAETH_API USkillNode : public UFaethObjectBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SkillDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SkillDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// The ability that will be given to the character
	TSubclassOf<UFaethGameplayAbility> SkillAbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// The effect that will be granted to the character
	TSubclassOf<UGameplayEffect> SkillEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
	// The amount of job points that will be paid to unlock this node
	int JobPointsCost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
	// The amount of skill points that will be paid to unlock this node
	int SkillPointsCost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// Set to true once the cost of unlocking the node has been paid
	bool bIsUnlocked = false;

	UPROPERTY(BlueprintReadWrite)
	TArray<USkillNodeLink*> NodeLinks;

protected:
	UPROPERTY(BlueprintReadOnly)
	// Set to true once the ability/effect has been given to the character
	bool bIsActivated = false;

public:
	USkillNodeLink* CreateNodeLinkTo(USkillNode* OtherNode);

	UFUNCTION(BlueprintCallable)
	// Gives the skill to the character if either the ability or effect class is set.
	void GiveSkillToCharacter(AFaethCharacter* Character);

	/* To do: RemoveSkillFromCharacter() */

	UFUNCTION(BlueprintNativeEvent)
	// A blueprint native event for checking all the unlock conditions for this node.
	// Default implementation checks if the unlock cost(s) can be paid.
	bool CheckUnlockConditions();
};
