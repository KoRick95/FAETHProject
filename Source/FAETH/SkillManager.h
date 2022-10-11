#pragma once

#include "CoreMinimal.h"
#include "FaethDataObject.h"
#include "SkillManager.generated.h"

class AFaethCharacter;

UCLASS()
class FAETH_API USkillManager : public UFaethDataObject
{
	GENERATED_BODY()
	
public:
	//TArray<USkill*>

protected:
	// To do: Turn this into an exposed UPROPERTY.
	AFaethCharacter* OwningCharacter;

public:
	UFUNCTION(BlueprintPure)
	AFaethCharacter* GetOwningCharacter();

	UFUNCTION(BlueprintCallable)
	void SetOwningCharacter(AFaethCharacter* NewCharacter);

protected:
	virtual void BeginPlay() override;
};
