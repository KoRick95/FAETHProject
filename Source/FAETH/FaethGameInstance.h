#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FaethGameInstance.generated.h"

class APlayerCharacter;
class UQuestManager;

UCLASS()
class FAETH_API UFaethGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, DisplayName = "Quest Manager")
	TSubclassOf<UQuestManager> QuestManagerClass;

	UPROPERTY(BlueprintReadOnly)
	UQuestManager* QuestManager;

	UPROPERTY(BlueprintReadWrite)
	APlayerCharacter* Player;

public:
	virtual void Init() override;
};
