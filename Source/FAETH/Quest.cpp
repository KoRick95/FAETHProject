#include "Quest.h"
#include "FaethFunctionLibrary.h"
#include "QuestManager.h"
#include "QuestObjective.h"
#include "QuestRewards.h"

void UQuest::Init(UQuestManager* OwningQuestManager)
{
	QuestManager = OwningQuestManager;

	for (auto objectiveClass : QuestObjectiveClasses)
	{
		UQuestObjective* objective = NewObject<UQuestObjective>(this, objectiveClass);
		objective->Init(this);
		Objectives.Add(objective);
	}
}

bool UQuest::IsQuestStatusBlocked(const FProgressStatusBlockFlags& Flags)
{
	return (QuestStatus == EProgressStatus::Locked && Flags.bBlockLocked) ||
		(QuestStatus == EProgressStatus::Unlocked && Flags.bBlockUnlocked) ||
		(QuestStatus == EProgressStatus::Started && Flags.bBlockStarted) ||
		(QuestStatus == EProgressStatus::Abandoned && Flags.bBlockAbandoned) ||
		(QuestStatus == EProgressStatus::Failed && Flags.bBlockFailed) ||
		(QuestStatus == EProgressStatus::Completed && Flags.bBlockCompleted);
}

int UQuest::GetActiveQuestStep()
{
	return ActiveQuestStep;
}

EProgressStatus UQuest::GetQuestStatus()
{
	return QuestStatus;
}

UQuestObjective* UQuest::GetObjectiveByID(FName ObjectiveID)
{
	for (UQuestObjective* objective : Objectives)
	{
		if (objective->ObjectiveID == ObjectiveID)
		{
			return objective;
		}
	}

	return nullptr;
}

UQuestObjective* UQuest::GetObjectiveByClass(TSubclassOf<UQuestObjective> ObjectiveClass)
{
	for (UQuestObjective* objective : Objectives)
	{
		if (objective->GetClass() == ObjectiveClass)
		{
			return objective;
		}
	}

	return nullptr;
}

const TArray<UQuestObjective*>& UQuest::GetObjectives()
{
	return Objectives;
}

const TArray<UQuestObjective*>& UQuest::GetActiveObjectives()
{
	return ActiveObjectives;
}

TArray<UQuestObjective*> UQuest::GetObjectivesByQuestStep(int Step)
{
	TArray<UQuestObjective*> objectives;

	if (Step < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Get objectives by group index failed: Invalid objective group index %i"), Step);
	}

	for (UQuestObjective* objective : Objectives)
	{
		objectives.Add(objective);
	}

	return objectives;
}

TArray<UQuestObjective*> UQuest::GetObjectivesByStatus(EProgressStatus ObjectiveStatus)
{
	TArray<UQuestObjective*> filteredObjectives;

	for (UQuestObjective* objective : Objectives)
	{
		if (objective->GetObjectiveStatus() == ObjectiveStatus)
		{
			filteredObjectives.Add(objective);
		}
	}

	return filteredObjectives;
}

void UQuest::SetActiveQuestStep(int Step, bool bHideInactiveObjectives)
{
	TArray<UQuestObjective*> newActiveObjectives = GetObjectivesByQuestStep(Step);
	
	for (UQuestObjective* objective : Objectives)
	{
		// Set active objectives as not hidden, and set inactive objectives as hidden if bHideInactiveObjectives is true.
		objective->bIsHidden = (objective->QuestStep == Step) ? false : (bHideInactiveObjectives ? true : objective->bIsHidden);
	}

	ActiveObjectives = newActiveObjectives;
	ActiveQuestStep = Step;
}

bool UQuest::HasQuestManager()
{
	return QuestManager->IsValidLowLevel();
}

bool UQuest::SetQuestStatus(EProgressStatus NewStatus, FProgressStatusBlockFlags Flags)
{
	if (QuestStatus == NewStatus)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set quest status failed: Passed status is the same as current status"));
		return false;
	}
	else if (NewStatus == EProgressStatus::Locked)
	{
		return LockQuest(Flags);
	}
	else if (NewStatus == EProgressStatus::Unlocked)
	{
		return UnlockQuest(Flags);
	}
	else if (NewStatus == EProgressStatus::Started)
	{
		return StartQuest(Flags);
	}
	else if (NewStatus == EProgressStatus::Abandoned)
	{
		return AbandonQuest(Flags);
	}
	else if (NewStatus == EProgressStatus::Failed)
	{
		return FailQuest(Flags);
	}
	else if (NewStatus == EProgressStatus::Completed)
	{
		return CompleteQuest(Flags);
	}

	return false;
}

bool UQuest::LockQuest(FProgressStatusBlockFlags Flags)
{
	if (!IsQuestStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Lock quest failed: Quest status is blocked."));
		return false;
	}

	QuestStatus = EProgressStatus::Locked;
	OnQuestLocked();
	UFaethFunctionLibrary::GetQuestManager(this)->OnAnyQuestLocked.Broadcast(this);

	return true;
}

bool UQuest::UnlockQuest(FProgressStatusBlockFlags Flags)
{
	if (IsQuestStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Unlock quest failed: Quest status is blocked."));
		return false;
	}

	QuestStatus = EProgressStatus::Unlocked;
	OnQuestUnlocked();
	UFaethFunctionLibrary::GetQuestManager(this)->OnAnyQuestUnlocked.Broadcast(this);

	return true;
}

bool UQuest::StartQuest(FProgressStatusBlockFlags Flags)
{
	if (IsQuestStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Unlock quest failed: Quest status is blocked."));
		return false;
	}

	QuestStatus = EProgressStatus::Started;
	OnQuestStarted();
	UFaethFunctionLibrary::GetQuestManager(this)->OnAnyQuestStarted.Broadcast(this);
	TimeLastStarted = FDateTime::UtcNow();

	return true;
}

bool UQuest::AbandonQuest(FProgressStatusBlockFlags Flags)
{
	if (IsQuestStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Abandon quest failed: Quest status is blocked."));
		return false;
	}

	QuestStatus = EProgressStatus::Abandoned;
	OnQuestAbandoned();
	UFaethFunctionLibrary::GetQuestManager(this)->OnAnyQuestAbandoned.Broadcast(this);
	TimeLastUpdated = FDateTime::UtcNow();

	return true;
}

bool UQuest::FailQuest(FProgressStatusBlockFlags Flags)
{
	if (IsQuestStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Fail quest failed: Quest status is blocked."));
		return false;
	}

	QuestStatus = EProgressStatus::Failed;
	OnQuestFailed();
	UFaethFunctionLibrary::GetQuestManager(this)->OnAnyQuestFailed.Broadcast(this);
	TimeLastUpdated = FDateTime::UtcNow();

	return true;
}

bool UQuest::CompleteQuest(FProgressStatusBlockFlags Flags)
{
	if (IsQuestStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Complete quest failed: Quest status is blocked."));
		return false;
	}

	QuestStatus = EProgressStatus::Completed;
	OnQuestCompleted();
	UFaethFunctionLibrary::GetQuestManager(this)->OnAnyQuestCompleted.Broadcast(this);
	TimeLastCompleted = FDateTime::UtcNow();

	return true;
}

bool UQuest::CheckCompletionConditions_Implementation()
{
	bool bIsCompleted = true;

	for (UQuestObjective* objective : Objectives)
	{
		if (objective->GetObjectiveStatus() != EProgressStatus::Completed)
		{
			bIsCompleted = false;
			break;
		}
	}

	return bIsCompleted;
}

void UQuest::OnQuestUpdated_Implementation()
{
	UFaethFunctionLibrary::GetQuestManager(this)->OnAnyQuestUpdated.Broadcast(this);
	TimeLastUpdated = FDateTime::UtcNow();
}

void UQuest::ResetProgress_Implementation()
{
	for (UQuestObjective* objective : Objectives)
	{
		objective->ResetProgress();
	}
}
