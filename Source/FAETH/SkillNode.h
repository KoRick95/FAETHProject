#pragma once

#include "CoreMinimal.h"
#include "FaethObjectBase.h"
#include "SkillNode.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class USkillNodeLink;

UCLASS()
class FAETH_API USkillNode : public UFaethObjectBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText NodeDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText NodeDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SkillPointsCost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int JobPointsCost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayAbility> AbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> EffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// Set to true once the cost of unlocking the node has been paid.
	bool bIsUnlocked = false;

	UPROPERTY(BlueprintReadWrite)
	TArray<USkillNodeLink*> NodeLinks;

protected:
	// Set to true once the ability/effect has been given to the character.
	bool bIsActivated = false;

public:
	USkillNodeLink* CreateNodeLinkTo(USkillNode* OtherNode);
};
