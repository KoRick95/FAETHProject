#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FaethGameInstance.generated.h"

class APlayerCharacter;
class UQuestManager;
class USkillManager;

UCLASS()
class FAETH_API UFaethGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Player")
	APlayerCharacter* Player;

	UPROPERTY(BlueprintReadOnly, Category = "Quest")
	UQuestManager* QuestManager;

	UPROPERTY(BlueprintReadOnly, Category = "Skill")
	USkillManager* SkillManager;

protected:
	// To do: Perhaps change the manager class to a subsystem instead? They are pretty much singletons.
	
	UPROPERTY(EditAnywhere, Category = "Quest", DisplayName = "Quest Manager")
	TSubclassOf<UQuestManager> QuestManagerClass;

	UPROPERTY(EditAnywhere, Category = "Skill", DisplayName = "Skill Manager")
	TSubclassOf<USkillManager> SkillManagerClass;

public:
	virtual void Init() override;
};
