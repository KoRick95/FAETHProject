#include "FaethFunctionLibrary.h"
#include "FaethGameInstance.h"
#include "Quest/Quest.h"
#include "Quest/QuestManager.h"
#include "Quest/QuestObjective.h"
#include "Kismet/GameplayStatics.h"

UFaethGameInstance* UFaethFunctionLibrary::GetFaethGameInstance(const UObject* WorldContextObject)
{
    return Cast<UFaethGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
}

UQuestManager* UFaethFunctionLibrary::GetQuestManager(const UObject* WorldContextObject)
{
    if (UFaethGameInstance* instance = GetFaethGameInstance(WorldContextObject))
    {
        return instance->QuestManager;
    }

    return nullptr;
}

UQuest* UFaethFunctionLibrary::GetQuestByClass(const TArray<UQuest*>& QuestArray, TSubclassOf<UQuest> QuestClass)
{
    for (UQuest* quest : QuestArray)
    {
        if (quest->GetClass() == QuestClass)
        {
            return quest;
        }
    }

    return nullptr;
}

UQuest* UFaethFunctionLibrary::GetQuestByID(const TArray<UQuest*>& QuestArray, FName QuestID)
{
    for (UQuest* quest : QuestArray)
    {
        if (quest->QuestID == QuestID)
        {
            return quest;
        }
    }

    return nullptr;
}

TArray<UQuest*> UFaethFunctionLibrary::GetQuestsByStatus(const TArray<UQuest*>& QuestArray, EProgressStatus QuestStatus)
{
    TArray<UQuest*> filteredQuests;

    for (UQuest* quest : QuestArray)
    {
        if (quest->GetQuestStatus() == QuestStatus)
        {
            filteredQuests.Add(quest);
        }
    }

    return filteredQuests;
}

UQuestObjective* UFaethFunctionLibrary::GetObjectiveByClass(const TArray<UQuestObjective*>& ObjectiveArray, TSubclassOf<UQuestObjective> ObjectiveClass)
{
    for (UQuestObjective* objective : ObjectiveArray)
    {
        if (objective->GetClass() == ObjectiveClass)
        {
            return objective;
        }
    }

    return nullptr;
}

UQuestObjective* UFaethFunctionLibrary::GetObjectiveByID(const TArray<UQuestObjective*>& ObjectiveArray, FName ObjectiveID)
{
    for (UQuestObjective* objective : ObjectiveArray)
    {
        if (objective->ObjectiveID == ObjectiveID)
        {
            return objective;
        }
    }

    return nullptr;
}

TArray<UQuestObjective*> UFaethFunctionLibrary::GetObjectivesByStatus(const TArray<UQuestObjective*>& ObjectiveArray, EProgressStatus ObjectiveStatus)
{
    TArray<UQuestObjective*> filteredObjectives;

    for (UQuestObjective* objective : ObjectiveArray)
    {
        if (objective->GetObjectiveStatus() == ObjectiveStatus)
        {
            filteredObjectives.Add(objective);
        }
    }

    return filteredObjectives;
}
