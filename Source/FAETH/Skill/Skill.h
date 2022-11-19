#pragma once

#include "CoreMinimal.h"
#include "../FaethAbility.h"
#include "../FaethObjectTypes.h"
#include "Skill.generated.h"

class AFaethCharacter;
class UFaethAbility;
class UFaethGameplayAbilitySystem;
class UGameplayEffect;
class USkillSystemComponent;

UCLASS()
class FAETH_API USkill : public UFaethAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

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
	UPROPERTY(EditAnywhere)
	// Set to true when the ability is granted to the character
	bool bEnabled = false;

	UPROPERTY(EditAnywhere)
	// Set to true if the ability is auto activated when granted to the character
	bool bAutoActivate = false;

	UFaethGameplayAbilitySystem* OwningComponent;

	// Set to true once the skill has been properly applied to the owning character
	bool bApplied = false;

public:
	UFUNCTION(BlueprintPure)
	const bool IsActivated() { return bEnabled; }

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
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};
