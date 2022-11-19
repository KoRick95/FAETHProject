#include "QuestObjective.h"
#include "Quest.h"
#include "QuestManager.h"
#include "../FaethFunctionLibrary.h"

bool UQuestObjective::IsObjectiveStatusBlocked(const FProgressStatusBlockFlags& Flags) const
{
	return (ObjectiveStatus == EProgressStatus::Locked && Flags.bBlockLocked) ||
		(ObjectiveStatus == EProgressStatus::Unlocked && Flags.bBlockUnlocked) ||
		(ObjectiveStatus == EProgressStatus::Started && Flags.bBlockStarted) ||
		(ObjectiveStatus == EProgressStatus::Abandoned && Flags.bBlockAbandoned) ||
		(ObjectiveStatus == EProgressStatus::Failed && Flags.bBlockFailed) ||
		(ObjectiveStatus == EProgressStatus::Completed && Flags.bBlockCompleted);
}

EProgressStatus UQuestObjective::GetObjectiveStatus() const
{
	return ObjectiveStatus;
}

FQuestObjectiveData UQuestObjective::GetObjectiveData() const
{
	return FQuestObjectiveData(this);
}

bool UQuestObjective::SetObjectiveStatus(EProgressStatus NewStatus, FProgressStatusBlockFlags Flags)
{
	if (ObjectiveStatus == NewStatus)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set objective status failed: Passed status is the same as current status"));
		return false;
	}
	else if (NewStatus == EProgressStatus::Locked)
	{
		return LockObjective(Flags);
	}
	else if (NewStatus == EProgressStatus::Unlocked)
	{
		return UnlockObjective(Flags);
	}
	else if (NewStatus == EProgressStatus::Started)
	{
		return StartObjective(Flags);
	}
	else if (NewStatus == EProgressStatus::Abandoned)
	{
		return AbandonObjective(Flags);
	}
	else if (NewStatus == EProgressStatus::Failed)
	{
		return FailObjective(Flags);
	}
	else if (NewStatus == EProgressStatus::Completed)
	{
		return CompleteObjective(Flags);
	}

	return false;
}

bool UQuestObjective::LockObjective(FProgressStatusBlockFlags Flags)
{
	if (IsObjectiveStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Lock objective failed: Objective status is blocked."));
		return false;
	}

	ObjectiveStatus = EProgressStatus::Locked;
	OnObjectiveLocked();
	UFaethFunctionLibrary::GetQuestManager(this)->OnAnyObjectiveLocked.Broadcast(this);

	return true;
}

bool UQuestObjective::UnlockObjective(FProgressStatusBlockFlags Flags)
{
	if (IsObjectiveStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Unlock objective failed: Objective status is blocked."));
		return false;
	}

	ObjectiveStatus = EProgressStatus::Unlocked;
	OnObjectiveUnlocked();
	UFaethFunctionLibrary::GetQuestManager(this)->OnAnyObjectiveUnlocked.Broadcast(this);

	return true;
}

bool UQuestObjective::StartObjective(FProgressStatusBlockFlags Flags)
{
	if (IsObjectiveStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Start objective failed: Objective status is blocked."));
		return false;
	}

	ObjectiveStatus = EProgressStatus::Started;
	OnObjectiveStarted();
	UFaethFunctionLibrary::GetQuestManager(this)->OnAnyObjectiveStarted.Broadcast(this);
	TimeLastStarted = FDateTime::UtcNow();

	return true;
}

bool UQuestObjective::AbandonObjective(FProgressStatusBlockFlags Flags)
{
	if (IsObjectiveStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Start objective failed: Objective status is blocked."));
		return false;
	}

	ObjectiveStatus = EProgressStatus::Abandoned;
	OnObjectiveAbandoned();
	UFaethFunctionLibrary::GetQuestManager(this)->OnAnyObjectiveAbandoned.Broadcast(this);
	TimeLastUpdated = FDateTime::UtcNow();

	return true;
}

bool UQuestObjective::FailObjective(FProgressStatusBlockFlags Flags)
{
	if (IsObjectiveStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Start objective failed: Objective status is blocked."));
		return false;
	}

	ObjectiveStatus = EProgressStatus::Failed;
	OnObjectiveFailed();
	UFaethFunctionLibrary::GetQuestManager(this)->OnAnyObjectiveFailed.Broadcast(this);
	TimeLastUpdated = FDateTime::UtcNow();

	return true;
}

bool UQuestObjective::CompleteObjective(FProgressStatusBlockFlags Flags)
{
	if (IsObjectiveStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Start objective failed: Objective status is blocked."));
		return false;
	}

	ObjectiveStatus = EProgressStatus::Completed;
	OnObjectiveCompleted();
	UFaethFunctionLibrary::GetQuestManager(this)->OnAnyObjectiveCompleted.Broadcast(this);
	TimeLastCompleted = FDateTime::UtcNow();

	return true;
}

void UQuestObjective::OnObjectiveUpdated_Implementation()
{
	UFaethFunctionLibrary::GetQuestManager(this)->OnAnyObjectiveUpdated.Broadcast(this);
	TimeLastUpdated = FDateTime::UtcNow();
	Quest->OnQuestUpdated();
}