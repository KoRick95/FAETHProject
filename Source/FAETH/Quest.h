#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FaethObjectTypes.h"
#include "Quest.generated.h"

class UQuestManager;
class UQuestObjective;
class UQuestRewards;

UCLASS(Blueprintable)
class FAETH_API UQuest : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	UQuestManager* QuestManager;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	FName QuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Display Name", Category = "Quest")
	FText QuestDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Description", Category = "Quest")
	FText QuestDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	FText QuestGiverName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	FText QuestAreaName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	bool bIsHidden;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	bool bIsRepeatable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	bool bAllowRetryAbandoned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	int MaxAllowedFails;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	int MinReqLevel;

	UPROPERTY(EditAnywhere, DisplayName = "Objectives", Category = "Quest")
	TArray<TSubclassOf<UQuestObjective>> QuestObjectiveClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TSubclassOf<UQuestRewards> QuestRewards;

	UPROPERTY(BlueprintReadWrite, Category = "Quest")
	FDateTime TimeLastStarted;

	UPROPERTY(BlueprintReadWrite, Category = "Quest")
	FDateTime TimeLastUpdated;

	UPROPERTY(BlueprintReadWrite, Category = "Quest")
	FDateTime TimeLastCompleted;

private:
	UPROPERTY()
	EProgressStatus QuestStatus;

	UPROPERTY()
	TArray<UQuestObjective*> Objectives;
	
	UPROPERTY()
	TArray<UQuestObjective*> ActiveObjectives;

	UPROPERTY()
	int ActiveQuestStep;

public:
	virtual void PostInitProperties() override;

	// Returns true if the current quest status is being flagged to ignore.
	bool IsQuestStatusBlocked(const FProgressStatusBlockFlags& Flags) const;

	UFUNCTION(BlueprintCallable)
	EProgressStatus GetQuestStatus() const;

	UFUNCTION(BlueprintCallable)
	TArray<UQuestObjective*> GetObjectives() const;

	UFUNCTION(BlueprintCallable)
	TArray<UQuestObjective*> GetActiveObjectives() const;

	UFUNCTION(BlueprintCallable)
	int GetActiveQuestStep() const;

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// @return An array of objectives of the given quest step.
	TArray<UQuestObjective*> GetObjectivesByQuestStep(int Step) const;

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Sets all the objectives of the given quest step active.
	// @param bHideInactiveGroup = Sets all other objectives as hidden if set to true. Default value is true.
	void SetActiveQuestStep(int Step, bool bHideInactiveObjectives = true);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Convenience function that calls the appropriate status setter function depending on the NewStatus passed.
	// @return Preliminarily returns false if NewStatus is the same as current quest status.
	bool SetQuestStatus(EProgressStatus NewStatus, FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest is able to be locked, false otherwise.
	bool LockQuest(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest is able to be unlocked, false otherwise.
	bool UnlockQuest(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest is able to be started, false otherwise.
	bool StartQuest(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest is able to be abandoned, false otherwise.
	bool AbandonQuest(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest is able to be failed, false otherwise.
	bool FailQuest(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest is able to be completed, false otherwise.
	bool CompleteQuest(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quest")
	// Returns true if completion conditions are met.
	bool CheckCompletionConditions();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quest")
	void OnQuestUpdated();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quest")
	void ResetProgress();

	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void OnQuestLocked();

	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void OnQuestUnlocked();

	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void OnQuestStarted();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void OnQuestAbandoned();

	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void OnQuestFailed();

	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void OnQuestCompleted();
};
