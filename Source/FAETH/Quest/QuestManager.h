#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../FaethDataObject.h"
#include "../FaethObjectTypes.h"
#include "QuestManager.generated.h"

class UQuest;
class UQuestObjective;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestUpdated, UQuest*, Quest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveUpdated, UQuestObjective*, Objective);

UCLASS(Blueprintable)
class FAETH_API UQuestManager : public UFaethDataObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
	int MaxTrackedQuests = 1;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnQuestUpdated OnAnyQuestUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnQuestUpdated OnAnyQuestAdded;

	UPROPERTY(BlueprintAssignable)
	FOnQuestUpdated OnAnyQuestLocked;

	UPROPERTY(BlueprintAssignable)
	FOnQuestUpdated OnAnyQuestUnlocked;

	UPROPERTY(BlueprintAssignable)
	FOnQuestUpdated OnAnyQuestStarted;

	UPROPERTY(BlueprintAssignable)
	FOnQuestUpdated OnAnyQuestAbandoned;

	UPROPERTY(BlueprintAssignable)
	FOnQuestUpdated OnAnyQuestFailed;

	UPROPERTY(BlueprintAssignable)
	FOnQuestUpdated OnAnyQuestCompleted;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnObjectiveUpdated OnAnyObjectiveUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnObjectiveUpdated OnAnyObjectiveLocked;

	UPROPERTY(BlueprintAssignable)
	FOnObjectiveUpdated OnAnyObjectiveUnlocked;

	UPROPERTY(BlueprintAssignable)
	FOnObjectiveUpdated OnAnyObjectiveStarted;

	UPROPERTY(BlueprintAssignable)
	FOnObjectiveUpdated OnAnyObjectiveAbandoned;

	UPROPERTY(BlueprintAssignable)
	FOnObjectiveUpdated OnAnyObjectiveFailed;

	UPROPERTY(BlueprintAssignable)
	FOnObjectiveUpdated OnAnyObjectiveCompleted;

private:
	UPROPERTY()
	TArray<UQuest*> Quests;

	UPROPERTY()
	TArray<UQuest*> TrackedQuests;

public:
	virtual void PostInitProperties() override;

	UFUNCTION(BlueprintCallable)
	TArray<UQuest*> GetQuests() const;

	UFUNCTION(BlueprintCallable)
	TArray<UQuest*> GetTrackedQuests() const;

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest ID exist in the quest list.
	bool DoesQuestIDExist(FName QuestID);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Adds a new quest to the manager's quest list, and performs any necessary initialisation.
	// * bOverwriteDuplicateID = Whether the function overwrites any existing quest with the same ID.
	void AddNewQuest(UQuest* NewQuest, bool bOverwriteDuplicateID = false);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void TrackQuest(UQuest* Quest, bool bReplaceOldest = false);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuest*>& SortQuestsByDisplayName();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuest*>& SortQuestsByID();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuest*>& SortQuestsByStatus();

	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void Init();
};
