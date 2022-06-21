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
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayAbility> AbilityClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> EffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText NodeDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText NodeDescription;

	UPROPERTY(BlueprintReadWrite)
	TArray<USkillNodeLink*> NodeLinks;//contain both start link and end link?

public:
	// create link from node
	USkillNodeLink* CreateNodeLinkTo(USkillNode* OtherNode);
};
