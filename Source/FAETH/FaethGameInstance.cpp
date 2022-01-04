#include "FaethGameInstance.h"
#include "QuestManager.h"

void UFaethGameInstance::Init()
{
	Super::Init();

	QuestManager = (QuestManagerClass) ? NewObject<UQuestManager>(this, QuestManagerClass, "Quest Manager") : NewObject<UQuestManager>(this, UQuestManager::StaticClass(), "Quest Manager");
	QuestManager->Init();
}

UQuestManager* UFaethGameInstance::GetQuestManager()
{
	return QuestManager;
}
