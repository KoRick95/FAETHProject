#pragma once

#include "CoreMinimal.h"
#include "FaethObjectBase.h"
#include "SkillManager.generated.h"

class AFaethCharacter;

UCLASS()
class FAETH_API USkillManager : public UFaethObjectBase
{
	GENERATED_BODY()
	
public:


protected:
	AFaethCharacter* OwningCharacter;

public:
	UFUNCTION(BlueprintPure)
	AFaethCharacter* GetOwningCharacter();

	UFUNCTION(BlueprintCallable)
	void SetOwningCharacter(AFaethCharacter* NewCharacter);

	/* functions
	* node selector/navigation
	* call giveability or applygameplayeffecttoself from chara
	* refresh nodes/branches
	*/

protected:
	virtual void BeginPlay() override;
};
