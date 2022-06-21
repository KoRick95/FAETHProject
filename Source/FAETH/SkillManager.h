#pragma once

#include "CoreMinimal.h"
#include "FaethObjectBase.h"
#include "SkillManager.generated.h"

class UFaethCharacter;

UCLASS()
class FAETH_API USkillManager : public UFaethObjectBase
{
	GENERATED_BODY()
	
public:
	UFaethCharacter* OwningCharacter;

	/* functions
	* node selector/navigation
	* call giveability or applygameplayeffecttoself from chara
	* refresh nodes/branches
	*/
};
