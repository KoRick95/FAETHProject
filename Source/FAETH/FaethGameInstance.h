#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FaethGameInstance.generated.h"

class APlayableCharacter;
class UQuestManager;

UCLASS()
class FAETH_API UFaethGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Player")
	APlayableCharacter* Player;

	UPROPERTY(BlueprintReadOnly, Category = "Quest")
	UQuestManager* QuestManager;

protected:
	// To do: Perhaps change the manager class to a subsystem instead? They are pretty much singletons.
	
	UPROPERTY(EditAnywhere, Category = "Quest", DisplayName = "Quest Manager")
	TSubclassOf<UQuestManager> QuestManagerClass;

public:
	virtual void Init() override;
};
