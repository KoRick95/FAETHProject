#pragma once

#include "CoreMinimal.h"
#include "FaethCharacter.h"
#include "PlayableCharacter.generated.h"

UCLASS()
class FAETH_API APlayableCharacter : public AFaethCharacter
{
	GENERATED_BODY()

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
