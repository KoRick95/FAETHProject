#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FaethFunctionLibrary.generated.h"

class UQuestManager;

UCLASS()
class FAETH_API UFaethFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UQuestManager* GetQuestManager(const UObject* WorldContextObject);
};
