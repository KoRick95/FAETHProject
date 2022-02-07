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

	for (FQuestObjectiveData data : RelatedObjectivesData)
	{
		// Get quest ptr from the QuestManager.
		UQuest* quest = UFaethFunctionLibrary::GetQuestByClass(questManager->GetQuests(), data.QuestClass);
		
		// Get objective ptr if Quest is not null, otherwise set objective as null.
		UQuestObjective* objective = (quest) ? UFaethFunctionLibrary::GetObjectiveByClass(quest->GetObjectives(), data.ObjectiveClass) : nullptr;

		if (objective)
		{
			// If ptr exists, store the ptr to the array.
			InitialisedObjectives.Add(objective);
			UE_LOG(LogTemp, Display, TEXT("Successfully initiated objective: %s"), *objective->GetClass()->GetName());
		}
		else
		{
			// If ptr is null, add it to the array of unitialised objectives and bind the objective setter function later.
			UninitialisedObjectivesData.Add(data);
			bBindObjectiveSetter = true;
		}
	}

	if (bBindObjectiveSetter)
	{
		// Set the objective ptrs when its quest is added to the QuestManager.
		questManager->OnAnyQuestAdded.AddDynamic(this, &UQuestObjectiveComponent::SetObjectivesFromQuest);
	}
}

void UQuestObjectiveComponent::SetObjectivesFromQuest(UQuest* NewQuest)
{
	for (int i = 0; i < UninitialisedObjectivesData.Num(); ++i)
	{
		// If the objective has the same quest class as the new quest...
		if (UninitialisedObjectivesData[i].QuestClass == NewQuest->GetClass())
		{
			//If a matching objective is found, add it to the array of initialised objectives.
			if (UQuestObjective* objective = UFaethFunctionLibrary::GetObjectiveByClass(NewQuest->GetObjectives(), UninitialisedObjectivesData[i].ObjectiveClass))
			{
				InitialisedObjectives.Add(objective);
				UninitialisedObjectivesData.RemoveAt(i);
				i--;
				UE_LOG(LogTemp, Display, TEXT("Successfully initiated objective: %s"), *objective->GetClass()->GetName());
			}
		}
	}
}
