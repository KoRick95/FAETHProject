#pragma once

#include "CoreMinimal.h"
#include "../FaethDataObject.h"
#include "Skill.generated.h"

class APlayableCharacter;
class UFaethAbility;
class USkillSystemComponent;

UCLASS()
class FAETH_API USkill : public UFaethDataObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FName SkillID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SkillDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SkillDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UFaethAbility> AbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"), Category = "Unlock Requirements")
	float JobPointsCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"), Category = "Unlock Requirements")
	float SkillPointsCost;

	UPROPERTY(EditAnywhere, Category = "Unlock Requirements")
	// Other skills that need to be unlocked before this skill can be unlocked
	TArray<TSubclassOf<USkill>> PrerequisiteSkills;

	UPROPERTY(BlueprintReadOnly)
	// Whether this skill is currently unlocked for the owning character
	// Note: Try to avoid modifying this value directly. Use TryUnlockSkill() from the SkillSystemComponent instead.
	bool bUnlocked = false;

	UPROPERTY(BlueprintReadOnly)
	// Whether this skill is currently enabled for the owning character
	// Note: Try to avoid modifying this value directly. Use EnableSkill() / DisableSkill() from the SkillSystemComponent instead.
	bool bEnabled = false;

protected:
	// Cached pointer to the character which owns this skill
	APlayableCharacter* OwningCharacter;

public:
	UFUNCTION(BlueprintPure)
	// Returns the skill system component that owns this skill.
	USkillSystemComponent* GetSkillSystemComponent();

	UFUNCTION(BlueprintPure)
	// Returns the character which owns this skill.
	APlayableCharacter* GetOwningCharacter();

	UFUNCTION(BlueprintPure, BlueprintNativeEvent)
	// Returns true if the owning character can pay the unlock cost of this skill.
	bool CanPayUnlockCost();

	UFUNCTION(BlueprintPure, BlueprintNativeEvent)
	// A native function that is meant to be overridden in the derived classes.
	// Return should be true when the conditions are fulfilled.
	// Default implementation always returns true.
	bool CheckAdditionalUnlockConditions();

	UFUNCTION(BlueprintNativeEvent)
	// Returns true if the owning character successfully paid for the unlock cost of this skill.
	// To do: Currently facing restrictions from being unable to modify FGameplayAttributeData types. Will fix in the future.
	bool TryPayUnlockCost();
};
