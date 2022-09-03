#pragma once

#include "CoreMinimal.h"
#include "FaethDataObject.h"
#include "SkillManager.generated.h"

class AFaethCharacter;
class USkillNode;

USTRUCT(BlueprintType)
struct FSkillNodeSelector
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int Index;

	UPROPERTY(BlueprintReadOnly)
	USkillNode* Node;
};

UCLASS()
class FAETH_API USkillManager : public UFaethDataObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	TArray<USkillNode*> SkillNodes;

	UPROPERTY(BlueprintReadOnly, Category = "Navigation")
	FSkillNodeSelector NodeSelector;

protected:
	// To do: Turn this into an exposed UPROPERTY.
	AFaethCharacter* OwningCharacter;

public:
	UFUNCTION(BlueprintPure)
	AFaethCharacter* GetOwningCharacter();

	UFUNCTION(BlueprintCallable)
	void SetOwningCharacter(AFaethCharacter* NewCharacter);

	/* functions
	* node selector/navigation
	* refresh nodes/branches
	* create widget
	* widget holds node classes
	* init node classes and store into manager
	*/

	USkillNode* SelectNodeByIndex(int ArrayIndex);
	USkillNode* SelectNodePrev();
	USkillNode* SelectNodeNext();
	USkillNode* SelectNodeStart();
	USkillNode* SelectNodeEnd();

protected:
	virtual void BeginPlay() override;
};
