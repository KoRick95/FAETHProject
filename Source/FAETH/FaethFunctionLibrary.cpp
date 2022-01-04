#include "FaethFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "FaethGameInstance.h"
#include "QuestManager.h"

UQuestManager* UCustomFunctionLibrary::GetQuestManager(const UObject* WorldContextObject)
{
    if (UCustomGameInstance* instance = Cast<UFaethGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject)))
    {
        return instance->GetQuestManager();
    }

    return nullptr;
}
