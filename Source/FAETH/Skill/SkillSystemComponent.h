#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillSystemComponent.generated.h"

class AFaethCharacter;
class USkill;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FAETH_API USkillSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USkillSystemComponent();
	
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
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
};
