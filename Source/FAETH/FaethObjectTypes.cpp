#include "FaethObjectTypes.h"
#include "Quest.h"
#include "QuestObjective.h"

FQuestObjectivePair::FQuestObjectivePair(UQuestObjective* ObjectivePtr)
{
	if (ObjectivePtr)
	{
		Objective = ObjectivePtr;
		ObjectiveClass = ObjectivePtr->GetClass();

		if (ObjectivePtr->Quest)
		{
			Quest = ObjectivePtr->Quest;
			QuestClass = Quest->GetClass();
		}
	}
}
