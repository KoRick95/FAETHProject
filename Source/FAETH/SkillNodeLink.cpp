#include "SkillNodeLink.h"
#include "SkillNode.h"

void USkillNodeLink::SetNodes(USkillNode* Start, USkillNode* End)
{
	StartNode = Start;
	EndNode = End;
}
