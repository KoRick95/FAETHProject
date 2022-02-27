#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FaethObjectTypes.h"
#include "QuestObjective.generated.h"

class UQuest;

UENUM(BlueprintType)
enum class EQuestObjectiveType : uint8
{
	None,
	Travel,
	Interact,
	Collect,
	Kill
};

UCLASS(Blueprintable)
class FAETH_API UQuestObjective : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	UQuest* Quest;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ObjectiveID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Description")
	FText ObjectiveDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Type")
	EQuestObjectiveType ObjectiveType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsHidden;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
	// Determines which quest step this objective belongs to.
	// Multiple objectives can be assigned to the same step.
	int QuestStep;

	UPROPERTY(BlueprintReadOnly)
	FDateTime TimeLastStarted;

	UPROPERTY(BlueprintReadOnly)
	FDateTime TimeLastUpdated;

	UPROPERTY(BlueprintReadOnly)
	FDateTime TimeLastCompleted;

private:
	EProgressStatus ObjectiveStatus;

public:
	// Returns true if the current objective status is being flagged to ignore.
	bool IsObjectiveStatusBlocked(const FProgressStatusBlockFlags& Flags);

	UFUNCTION(BlueprintCallable)
	EProgressStatus GetObjectiveStatus();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	FQuestObjectiveData GetObjectiveData();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Convenience function that calls the appropriate status changing function depending on the NewStatus passed.
	// Preliminarily returns false if NewStatus is the same as current objective status.
	bool SetObjectiveStatus(EProgressStatus NewStatus, FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if objective is able to be locked, false otherwise.
	bool LockObjective(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest is able to be unlocked, false otherwise.
	bool UnlockObjective(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest is able to be started, false otherwise.
	bool StartObjective(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest is able to be abandoned, false otherwise.
	bool AbandonObjective(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest is able to be failed, false otherwise.
	bool FailObjective(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	// Returns true if quest is able to be completed, false otherwise.
	bool CompleteObjective(FProgressStatusBlockFlags Flags);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ResetProgress();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnObjectiveUpdated();

	UFUNCTION(BlueprintImplementableEvent)
	void OnObjectiveLocked();

	UFUNCTION(BlueprintImplementableEvent)
	void OnObjectiveUnlocked();

	UFUNCTION(BlueprintImplementableEvent)
	void OnObjectiveStarted();

	UFUNCTION(BlueprintImplementableEvent)
	void OnObjectiveAbandoned();

	UFUNCTION(BlueprintImplementableEvent)
	void OnObjectiveFailed();

	UFUNCTION(BlueprintImplementableEvent)
	void OnObjectiveCompleted();
};
