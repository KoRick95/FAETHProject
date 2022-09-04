#pragma once

#include "CoreMinimal.h"
#include "FaethDataObject.h"
#include "FaethObjectTypes.h"
#include "Skill.generated.h"

class AFaethCharacter;
class UFaethGameplayAbility;
class UGameplayEffect;
class USkillSetComponent;

UCLASS()
class FAETH_API USkill : public UFaethDataObject
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
	bool bUnlocked = false;

protected:
	UPROPERTY(BlueprintReadOnly)
	USkillSetComponent* OwningComponent;

	UPROPERTY(EditAnywhere)
	// If set to true before runtime, then the skill will be applied on BeginPlay
	// Otherwise, this is only modified by ActivateSkill() or DeactivateSkill()
	bool bActivated = false;

	// Set to true once the skill has been properly applied to the owning character
	bool bApplied = false;

public:
	UFUNCTION(BlueprintPure)
	const bool IsActivated() { return bActivated; }

	UFUNCTION(BlueprintPure)
	const bool IsApplied() { return bApplied; }

	UFUNCTION(BlueprintPure)
	// Returns the owning character of the owning skill set component
	AFaethCharacter* GetOwningCharacter();

	UFUNCTION(BlueprintCallable)
	// Activates the skill on the owning character
	void ActivateSkill();

	UFUNCTION(BlueprintCallable)
	// Deactivates the skill on the owning character
	void DeactivateSkill();
	
	// Applies the skill to the character if either the ability or effect class is set
	void ApplySkillTo(AFaethCharacter* Character);

	// Removes the skill from the character if it has been applied
	void RemoveSkillFrom(AFaethCharacter* Character);

protected:
	virtual void BeginPlay() override;
};
