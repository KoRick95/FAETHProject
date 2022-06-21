#pragma once

#include "CoreMinimal.h"
#include "FaethObjectBase.h"
#include "SkillNodeLink.generated.h"

class USkillNode;

UCLASS()
class FAETH_API USkillNodeLink : public UFaethObjectBase
{
	GENERATED_BODY()
	
public:
	USkillNodeLink() {}
	USkillNodeLink(USkillNode* StartNode, USkillNode* EndNode) : StartNode(StartNode), EndNode(EndNode) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int JobPointCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SkillPointCost;

	UPROPERTY(BlueprintReadWrite)
	USkillNode* StartNode;

	UPROPERTY(BlueprintReadWrite)
	USkillNode* EndNode;

public:
	// custom check function
};
