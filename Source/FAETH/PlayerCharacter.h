#pragma once

#include "CoreMinimal.h"
#include "FaethCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FAETH_API APlayerCharacter : public AFaethCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Experience;
};
