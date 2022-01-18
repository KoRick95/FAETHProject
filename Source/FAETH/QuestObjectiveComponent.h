#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FaethObjectTypes.h"
#include "QuestObjectiveComponent.generated.h"

class UQuest;
class UQuestObjective;

UCLASS( ClassGroup=(Faeth), meta=(BlueprintSpawnableComponent) )
class FAETH_API UQuestObjectiveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UQuestObjectiveComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	TArray<FQuestObjectivePair> RelatedQuestObjectivePairs;

public:
	virtual void BeginPlay() override;

	void Init();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	TArray<UQuestObjective*> GetInitialisedObjectives();

	UFUNCTION(BlueprintCallable, Category = "Quest", DisplayName = "Set Objective Refs From Quest")
	void SetObjectivesFromQuest(UQuest* NewQuest);
};
