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

	UPROPERTY(BlueprintReadWrite)
	UWidget* Widget;

	UPROPERTY(BlueprintReadWrite)
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
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	int GetCurrentIndex() { return WidgetNavigator.Index; }

	UFUNCTION(BlueprintCallable, Category = "Navigation")
	UWidget* GetCurrentWidget() { return WidgetNavigator.Widget; }

	UFUNCTION(BlueprintCallable, Category = "Navigation")
	virtual void NavigateByIndex(int Index);

	UFUNCTION(BlueprintCallable, Category = "Navigation")
	virtual void NagivateNext();

	UFUNCTION(BlueprintCallable, Category = "Navigation")
	virtual void NavigatePrev();

	UFUNCTION(BlueprintCallable, Category = "Navigation")
	virtual void NavigateStart();

	UFUNCTION(BlueprintCallable, Category = "Navigation")
	virtual void NavigateEnd();

protected:
	void UpdateNavigator(UWidget* NewWidget, int NewIndex);
};
