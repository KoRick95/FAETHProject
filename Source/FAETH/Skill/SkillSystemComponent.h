#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillSystemComponent.generated.h"

class APlayableCharacter;
class USkill;

UCLASS(Blueprintable)
class FAETH_API USkillSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	// An array of skill classes that gets instantiated on BeginPlay
	TArray<TSubclassOf<USkill>> InitialSkills;

protected:
	UPROPERTY()
	// An array of all the instantiated skills
	TArray<USkill*> Skills;

public:
	UFUNCTION(BlueprintPure)
	// Returns a copy of the instantiated skills array.
	TArray<USkill*> GetAllSkills() { return Skills; }

	UFUNCTION(BlueprintPure)
	// Returns an array of currently unlocked skills.
	TArray<USkill*> GetUnlockedSkills();

	UFUNCTION(BlueprintPure)
	// Returns the first skill in the array that has the exact matching class.
	USkill* GetSkillByClass(TSubclassOf<USkill> SkillClass);

	UFUNCTION(BlueprintPure)
	// Returns the first skill in the array that has a matching skill ID.
	USkill* GetSkillByID(FName SkillID);

	UFUNCTION(BlueprintPure)
	// Returns the cast result of this component's owner.
	APlayableCharacter* GetOwningCharacter();

	UFUNCTION(BlueprintPure)
	// Returns the attribute set of GetOwningCharacter().
	UCharacterAttributeSet* GetOwningCharacterAttributeSet();

	UFUNCTION(BlueprintCallable)
	void AddNewSkill(USkill* NewSkill);

	UFUNCTION(BlueprintPure, Category = "Skill Unlocking")
	// Returns true if the owning character has unlocked all of the prerequisites of the given skill.
	bool HasMetPrerequisiteConditions(USkill* Skill);

	UFUNCTION(BlueprintPure, Category = "Skill Unlocking")
	// Returns true if the owning character is eligible to unlock the given skill.
	bool CanUnlockSkill(USkill* Skill);

	UFUNCTION(BlueprintCallable, Category = "Skill Unlocking")
	// Attempts to unlock the skill and pay any associated costs.
	// @param Skill This is the skill to unlock (must exist in this component).
	// @param AutoEnable If set to true, it will automatically enables the skill for the owning character.
	// @return Returns true if the skill was successfully unlocked.
	bool TryUnlockSkill(USkill* Skill, bool bAutoEnable = true);

	UFUNCTION(BlueprintCallable)
	// Enables the given skill for the owning character.
	void EnableSkill(USkill* Skill);

	UFUNCTION(BlueprintCallable)
	// Disables the given skill for the owning character.
	void DisableSkill(USkill* Skill);

protected:
	virtual void BeginPlay() override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
};
