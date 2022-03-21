#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FaethObjectBase.generated.h"

UCLASS(Blueprintable, BlueprintType)
class FAETH_API UFaethObjectBase : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	virtual UWorld* GetWorld() const;
};
