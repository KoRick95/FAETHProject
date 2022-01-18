#include "FaethGameInstance.h"
#include "QuestManager.h"

void UFaethGameInstance::Init()
{
	Super::Init();

	QuestManagerClass = (QuestManagerClass) ? QuestManagerClass : UQuestManager::StaticClass();
	QuestManager = NewObject<UQuestManager>(this, QuestManagerClass, "Quest Manager");
	QuestManager->Init();
}

UQuestManager* UFaethGameInstance::GetQuestManager()
{
	return QuestManager;
}
