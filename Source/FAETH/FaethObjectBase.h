#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FaethObjectBase.generated.h"

UCLASS(Blueprintable, BlueprintType)
class FAETH_API UFaethObjectBase : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	virtual UWorld* GetWorld() const override;

protected:
	virtual void PostInitProperties() override;
	
	virtual void BeginPlay();

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "BeginPlay")
	void OnBeginPlay();
};
