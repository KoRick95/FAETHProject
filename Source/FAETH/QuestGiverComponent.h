#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FaethObjectTypes.h"
#include "QuestGiverComponent.generated.h"

class UQuest;

UCLASS( ClassGroup=(Faeth), meta=(BlueprintSpawnableComponent) )
class FAETH_API UQuestGiverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UQuestGiverComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TArray<TSubclassOf<UQuest>> QuestClasses;

private:
	UPROPERTY(BlueprintGetter = GetQuests, Category = "Quest")
	TArray<UQuest*> Quests;

public:
	virtual void BeginPlay() override;

	virtual void Init();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	TArray<UQuest*> GetQuests();
};
