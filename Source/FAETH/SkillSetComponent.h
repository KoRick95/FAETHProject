#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillSetComponent.generated.h"

class AFaethCharacter;
class USkill;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FAETH_API USkillSetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USkillSetComponent();
	
	UPROPERTY(BlueprintReadWrite)
	TArray<USkill*> SkillSet;

	UPROPERTY(BlueprintReadOnly)
	AFaethCharacter* OwningCharacter;

public:
	UFUNCTION(BlueprintPure)
	// Returns the first instance of the skill with the matching class
	USkill* GetSkillByClass(TSubclassOf<USkill> SkillClass);

	UFUNCTION(BlueprintCallable)
	void ActivateSkill(USkill* Skill);

	UFUNCTION(BlueprintCallable)
	void DeactivateSkill(USkill* Skill);

protected:
	virtual void BeginPlay() override;
};
