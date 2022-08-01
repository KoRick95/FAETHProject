#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FaethUserWidget.generated.h"

USTRUCT(BlueprintType)
struct FWidgetNavigator
{
	GENERATED_BODY()

public:
	FWidgetNavigator() {}
	FWidgetNavigator(UWidget* InWidget, int InIndex) : Widget(InWidget), Index(InIndex) {}

	UPROPERTY(BlueprintReadOnly)
	UWidget* Widget;

	UPROPERTY(BlueprintReadOnly)
	int Index;
};

UCLASS()
class FAETH_API UFaethUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "Navigation")
	TArray<UWidget*> NavigableWidgets;

	UPROPERTY(BlueprintReadOnly, Category = "Navigation")
	FWidgetNavigator WidgetNavigator;

public:
	
};
