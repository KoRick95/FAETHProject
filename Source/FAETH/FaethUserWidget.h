#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FaethObjectTypes.h"
#include "FaethUserWidget.generated.h"

USTRUCT(BlueprintType)
struct FWidgetNavigator
{
	GENERATED_BODY()

public:
	FWidgetNavigator() {}
	FWidgetNavigator(UWidget* InWidget, int InIndex) : CurrentWidget(InWidget), Index(InIndex) {}

	UPROPERTY(BlueprintReadOnly)
	UWidget* CurrentWidget;

	UPROPERTY(BlueprintReadOnly)
	UWidget* PreviousWidget;

	UPROPERTY(BlueprintReadOnly)
	int Index;
};

UCLASS()
class FAETH_API UFaethUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation")
	// If set to true, the navigation will wrap around the array.
	// I.e. Navigating next from the end of the array will go back to the start and vice versa.
	bool bWrapAround = false;
	
	UPROPERTY(BlueprintReadWrite, Category = "Navigation")
	TArray<UWidget*> NavigableWidgets;

	UPROPERTY(BlueprintReadOnly, Category = "Navigation")
	FWidgetNavigator WidgetNavigator;

public:
	UFUNCTION(BlueprintPure)
	TArray<UWidget*> GetChildren();

	UFUNCTION(BlueprintPure)
	TArray<UWidget*> GetChildrenOfClass(TSubclassOf<UWidget> WidgetClass);

	UFUNCTION(BlueprintCallable, Category = "Navigation")
	UWidget* GetCurrentWidget() { return WidgetNavigator.CurrentWidget; }

	UFUNCTION(BlueprintCallable, Category = "Navigation")
	UWidget* GetPreviousWidget() { return WidgetNavigator.PreviousWidget; }

	

	UFUNCTION(BlueprintImplementableEvent, Category = "Navigation")
	void OnNavigation();

protected:
	virtual FNavigationReply NativeOnNavigation(const FGeometry& MyGeometry, const FNavigationEvent& InNavigationEvent, const FNavigationReply& InDefaultReply) override;

	void UpdateNavigator(UWidget* NewWidget, int NewIndex);
};
