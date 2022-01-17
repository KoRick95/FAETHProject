#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FaethFunctionLibrary.generated.h"

class UFaethGameInstance;
class UQuest;
class UQuestManager;
class UQuestObjective;

UCLASS()
class FAETH_API UFaethFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UFaethGameInstance* GetFaethGameInstance(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UQuestManager* GetQuestManager(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Quest")
	static UQuest* GetQuestByClass(const TArray<UQuest*>& QuestArray, TSubclassOf<UQuest> QuestClass);

	UFUNCTION(BlueprintPure, Category = "Quest")
	static UQuest* GetQuestByID(const TArray<UQuest*>& QuestArray, FName QuestID);

	UFUNCTION(BlueprintPure, Category = "Quest")
	static UQuestObjective* GetObjectiveByClass(const TArray<UQuestObjective*>& ObjectiveArray, TSubclassOf<UQuestObjective> ObjectiveClass);

	UFUNCTION(BlueprintPure, Category = "Quest")
	static UQuestObjective* GetObjectiveByID(const TArray<UQuestObjective*>& ObjectiveArray, FName ObjectiveID);
};
