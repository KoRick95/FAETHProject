#include "QuestGiverComponent.h"
#include "FaethFunctionLibrary.h"
#include "Quest.h"
#include "QuestManager.h"

UQuestGiverComponent::UQuestGiverComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UQuestGiverComponent::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void UQuestGiverComponent::Init()
{
	UQuestManager* questManager = UFaethFunctionLibrary::GetQuestManager(this);

	if (!questManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Init assigned quests failed: Quest Manager is null."));
		return;
	}

	for (auto questClass : QuestClasses)
	{
		// Get quest ptr from the QuestManager.
		UQuest* quest = UFaethFunctionLibrary::GetQuestByClass(questManager->GetQuests(), questClass);

		// If ptr is null, create a new quest object.
		quest = (quest) ? quest : NewObject<UQuest>(this, questClass);

		// Store the ptr to the array.
		Quests.Add(quest);
	}
}

const TArray<UQuest*>& UQuestGiverComponent::GetQuests()
{
	return Quests;
}
