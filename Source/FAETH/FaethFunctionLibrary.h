#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FaethObjectTypes.h"
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
	static TArray<UQuest*> GetQuestsByStatus(const TArray<UQuest*>& QuestArray, EProgressStatus QuestStatus);

	UFUNCTION(BlueprintPure, Category = "Quest")
	static UQuestObjective* GetObjectiveByClass(const TArray<UQuestObjective*>& ObjectiveArray, TSubclassOf<UQuestObjective> ObjectiveClass);

	UFUNCTION(BlueprintPure, Category = "Quest")
	static UQuestObjective* GetObjectiveByID(const TArray<UQuestObjective*>& ObjectiveArray, FName ObjectiveID);

	UFUNCTION(BlueprintPure, Category = "Quest")
	static TArray<UQuestObjective*> GetObjectivesByStatus(const TArray<UQuestObjective*>& ObjectiveArray, EProgressStatus ObjectiveStatus);
};
