#include "FaethGameInstance.h"
#include "Character/PlayerCharacter.h"
#include "Quest/QuestManager.h"
#include "Skill/SkillManager.h"

#include "AbilitySystemGlobals.h"

void UFaethGameInstance::Init()
{
	Super::Init();
	UAbilitySystemGlobals::Get().InitGlobalData();

	QuestManagerClass = (QuestManagerClass) ? QuestManagerClass : UQuestManager::StaticClass();
	QuestManager = NewObject<UQuestManager>(this, QuestManagerClass, "QuestManager");

	SkillManagerClass = (SkillManagerClass) ? SkillManagerClass : USkillManager::StaticClass();
	SkillManager = NewObject<USkillManager>(this, SkillManagerClass, "SkillManager");
}
