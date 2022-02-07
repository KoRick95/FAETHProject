#include "QuestObjectiveComponent.h"
#include "FaethFunctionLibrary.h"
#include "Quest.h"
#include "QuestManager.h"
#include "QuestObjective.h"

UQuestObjectiveComponent::UQuestObjectiveComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UQuestObjectiveComponent::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void UQuestObjectiveComponent::Init()
{
	UQuestManager* questManager = UFaethFunctionLibrary::GetQuestManager(this);

	if (!questManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Requesting objective pointers failed: Quest Manager is null."));
		return;
	}

	bool bBindObjectiveSetter = false;

	for (FQuestObjectivePair pair : QuestObjectivePairs)
	{
		// Get quest ptr from the QuestManager.
		UQuest* quest = UFaethFunctionLibrary::GetQuestByClass(questManager->GetQuests(), pair.QuestClass);
		
		// Get objective ptr if Quest is not null, otherwise set objective as null.
		UQuestObjective* objective = (quest) ? UFaethFunctionLibrary::GetObjectiveByClass(quest->GetObjectives(), pair.ObjectiveClass) : nullptr;

		if (objective)
		{
			// If ptr exists, store the ptr to the objective info.
			pair.Objective = objective;
		}
		else
		{
			// If ptr is null, bind an objective setter function later.
			bBindObjectiveSetter = true;
		}
	}

	if (bBindObjectiveSetter)
	{
		// Set the objective ptrs when its quest is added to the QuestManager.
		questManager->OnAnyQuestAdded.AddDynamic(this, &UQuestObjectiveComponent::SetObjectivesFromQuest);
		UE_LOG(LogTemp, Display, TEXT("Binding objective setter to Quest Manager..."));
	}
}

TArray<UQuestObjective*> UQuestObjectiveComponent::GetInitialisedObjectives()
{
	TArray<UQuestObjective*> objectives;

	for (FQuestObjectivePair pair : QuestObjectivePairs)
	{
		UE_LOG(LogTemp, Display, TEXT("Checking quest objective %s."), *pair.ObjectiveClass.Get()->GetFName().ToString());

		if (pair.Objective)
		{
			UE_LOG(LogTemp, Display, TEXT("Found an initialised quest objective."));
			objectives.Add(pair.Objective);
		}
	}
	
	return objectives;
}

void UQuestObjectiveComponent::SetObjectivesFromQuest(UQuest* NewQuest)
{
	UE_LOG(LogTemp, Display, TEXT("Calling objective setter from a newly added quest."));
	for (FQuestObjectivePair pair : QuestObjectivePairs)
	{
		// If the objective ptr already exists, continue to the next objective info.
		if (pair.Objective)
		{
			UE_LOG(LogTemp, Display, TEXT("Objective already exists, skipping to the next objective."));
			continue;
		}

		// If the objective has the same quest class as the new quest...
		if (pair.QuestClass == NewQuest->GetClass())
		{
			UE_LOG(LogTemp, Display, TEXT("Found a matching quest..."));
			//If a matching objective is found, set it as the new objective ptr.
			if (UQuestObjective* objective = UFaethFunctionLibrary::GetObjectiveByClass(NewQuest->GetObjectives(), pair.ObjectiveClass))
			{
				UE_LOG(LogTemp, Display, TEXT("Found the objective to set."));
				pair.Objective = objective;
			}
		}
	}
}
