#pragma once

#include "CoreMinimal.h"
#include "FaethDataObject.h"
#include "SkillNode.generated.h"

class UFaethAbility;
class UGameplayEffect;
class USkillManager;
class USkillNodeLink;
class AFaethCharacter;

UCLASS()
class FAETH_API USkillNode : public UFaethDataObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SkillDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SkillDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// The ability that will be given to the character
	TSubclassOf<UFaethAbility> SkillAbilityClass;

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

protected:
	// The owning skill manager of this node
	USkillManager* SkillManager;

	UPROPERTY(BlueprintReadOnly)
	// Set to true once the ability/effect has been given to the character
	bool bIsActivated = false;

public:
	UFUNCTION(BlueprintPure)
	AFaethCharacter* GetOwningCharacter();

	UFUNCTION(BlueprintPure)
	USkillManager* GetSkillManager();
	
	UFUNCTION(BlueprintCallable)
	void SetSkillManager(USkillManager* NewSkillManager);

	UFUNCTION(BlueprintCallable)
	// Gives the skill to the character if either the ability or effect class is set.
	void GiveSkillToCharacter(AFaethCharacter* Character);

	/* To do: RemoveSkillFromCharacter() */
	UFUNCTION(BlueprintCallable)
	void RemoveSkillFromCharacter(AFaethCharacter* Character);

	UFUNCTION(BlueprintNativeEvent)
	// A blueprint native event for checking all the unlock conditions for this node.
	// Default implementation checks if the unlock cost(s) can be paid.
	bool CheckUnlockConditions();

protected:
	virtual void BeginPlay() override;
};
