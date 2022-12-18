#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FaethObjectTypes.generated.h"

class UQuest;
class UQuestObjective;

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	None			UMETA(DisplayName = "None"),
	Confirm			UMETA(DisplayName = "Confirm"),
	Cancel			UMETA(DisplayName = "Cancel"),
	Sprint			UMETA(DisplayName = "Sprint"),
	LightAttack		UMETA(DisplayName = "Light Attack"),
	HeavyAttack		UMETA(DisplayName = "Heavy Attack"),
	Dodge			UMETA(DisplayName = "Dodge"),
	Block			UMETA(DisplayName = "Block"),
	UseItem			UMETA(DisplayName = "Use Item"),
};

UENUM(BlueprintType)
enum class EConditionType : uint8
{
	AND		UMETA(ToolTip = "All AND type conditions must be met."),
	OR		UMETA(ToolTip = "At least one of an OR type condition must be met."),
	NOT		UMETA(ToolTip = "All NOT conditions must not be met (relative to their AND counterpart).")
};

UENUM(BlueprintType)
enum class EProgressStatus : uint8
{
	Locked,
	Unlocked,
	Started,
	Abandoned,
	Failed,
	Completed,
};

USTRUCT(BlueprintType)
struct FProgressStatusBlockFlags
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBlockLocked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBlockUnlocked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBlockStarted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBlockAbandoned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBlockFailed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBlockCompleted;
};

USTRUCT(BlueprintType)
struct FQuestObjectiveData
{
	GENERATED_BODY()

public:
	FQuestObjectiveData() {}
	FQuestObjectiveData(const UQuestObjective* ObjectivePtr);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UQuest> QuestClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UQuestObjective> ObjectiveClass;
};
