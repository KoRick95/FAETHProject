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

	for (FQuestObjectivePair pair : RelatedQuestObjectivePairs)
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
	}
}

TArray<UQuestObjective*> UQuestObjectiveComponent::GetInitialisedObjectives()
{
	TArray<UQuestObjective*> objectives;

	for (FQuestObjectivePair pair : RelatedQuestObjectivePairs)
	{
		if (pair.Objective)
		{
			objectives.Add(pair.Objective);
		}
	}
	
	return objectives;
}

void UQuestObjectiveComponent::SetObjectivesFromQuest(UQuest* NewQuest)
{
	for (FQuestObjectivePair pair : RelatedQuestObjectivePairs)
	{
		// If the objective ptr already exists, continue to the next objective info.
		if (pair.Objective)
		{
			continue;
		}

		// If the objective has the same quest class as the new quest...
		if (pair.QuestClass == NewQuest->GetClass())
		{
			//If a matching objective is found, set it as the new objective ptr.
			if (UQuestObjective* objective = UFaethFunctionLibrary::GetObjectiveByClass(NewQuest->GetObjectives(), pair.ObjectiveClass))
			{
				pair.Objective = objective;
			}
		}
	}
}
