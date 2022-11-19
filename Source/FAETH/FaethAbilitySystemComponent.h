#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "FaethAbilitySystemComponent.generated.h"

class USkill;

UCLASS()
class FAETH_API UFaethAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Skill")
	TArray<USkill*> UnlockableSkills;

public:
	UFUNCTION(BlueprintPure)
	// Returns the first instance of the skill with the matching class
	USkill* GetSkillByClass(TSubclassOf<USkill> SkillClass);


	bool UnlockSkill(USkill* Skill);


	bool ActivateSkill(USkill* Skill);
};
