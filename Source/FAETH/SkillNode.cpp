#include "SkillNode.h"
#include "SkillNodeLink.h"

USkillNodeLink* USkillNode::CreateNodeLinkTo(USkillNode* OtherNode)
{
	for (int i = 0; i < NodeLinks.Num(); ++i)
	{
		if (NodeLinks[i]->EndNode == OtherNode)
		{
			UE_LOG(LogTemp, Warning, TEXT("Create node link failed: Node link from %s to %s already exists."), *GetName(), *OtherNode->GetName());
			return nullptr;
		}
	}

	USkillNodeLink* NewLink = NewObject<USkillNodeLink>();
	NewLink->SetNodes(this, OtherNode);
	NodeLinks.Add(NewLink);

	return NewLink;
}
