#pragma once

#include "CoreMinimal.h"
#include "FaethCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FAETH_API APlayerCharacter : public AFaethCharacter
{
	GENERATED_BODY()

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
