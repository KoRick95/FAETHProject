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
	TArray<TSubclassOf<UQuest>> AssignedQuestClasses;

private:
	TArray<UQuest*> AssignedQuests;

public:
	virtual void BeginPlay() override;

	void Init();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	UQuest* GetQuestByClass(TSubclassOf<UQuest> QuestClass);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	UQuest* GetQuestByID(FName QuestID);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	TArray<UQuest*> GetAssignedQuests();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	TArray<UQuest*> GetQuestsByStatus(EProgressStatus QuestStatus);
};
