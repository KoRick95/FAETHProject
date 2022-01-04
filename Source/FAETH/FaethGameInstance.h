#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FaethGameInstance.generated.h"

class UQuestManager;

UCLASS()
class FAETH_API UFaethGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, DisplayName = "Quest Manager")
	TSubclassOf<UQuestManager> QuestManagerClass;

private:
	UQuestManager* QuestManager;

public:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable, Category = "Quest")
	UQuestManager* GetQuestManager();
};
