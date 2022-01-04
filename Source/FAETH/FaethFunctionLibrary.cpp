#include "FaethFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "FaethGameInstance.h"
#include "QuestManager.h"

UQuestManager* UFaethFunctionLibrary::GetQuestManager(const UObject* WorldContextObject)
{
    if (UFaethGameInstance* instance = Cast<UFaethGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject)))
    {
        return instance->GetQuestManager();
    }

    return nullptr;
}
