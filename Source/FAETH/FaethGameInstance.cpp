#include "FaethGameInstance.h"
#include "Character/PlayableCharacter.h"
#include "Quest/QuestManager.h"

#include "AbilitySystemGlobals.h"

void UFaethGameInstance::Init()
{
	Super::Init();
	UAbilitySystemGlobals::Get().InitGlobalData();

	QuestManagerClass = (QuestManagerClass) ? QuestManagerClass : UQuestManager::StaticClass();
	QuestManager = NewObject<UQuestManager>(this, QuestManagerClass, "QuestManager");
}
