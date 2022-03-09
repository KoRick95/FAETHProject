#include "FaethObjectTypes.h"
#include "Quest.h"
#include "QuestObjective.h"

FQuestObjectiveData::FQuestObjectiveData(const UQuestObjective* ObjectivePtr)
{
	if (ObjectivePtr)
	{
		ObjectiveClass = ObjectivePtr->GetClass();

		if (UQuest* quest = ObjectivePtr->Quest)
		{
			QuestClass = quest->GetClass();
		}
	}
}
