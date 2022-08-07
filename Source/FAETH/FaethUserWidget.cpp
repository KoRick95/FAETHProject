#include "FaethUserWidget.h"

void UFaethUserWidget::NavigateByIndex(int Index)
{
	if (Index >= 0 && Index < NavigableWidgets.Num())
	{
		UpdateNavigator(NavigableWidgets[Index], Index);
	}
	else if (Index < 0)
	{
		NavigateStart();
	}
	else if (Index >= NavigableWidgets.Num())
	{
		NavigateEnd();
	}
}

void UFaethUserWidget::NagivateNext()
{
	int NewIndex = GetCurrentIndex() + 1;

	if (NewIndex < NavigableWidgets.Num())
	{
		UpdateNavigator(NavigableWidgets[NewIndex], NewIndex);
	}
	else if (bWrapAround)
	{
		NavigateStart();
	}
}

void UFaethUserWidget::NavigatePrev()
{
	int NewIndex = GetCurrentIndex() - 1;

	if (NewIndex >= 0)
	{
		UpdateNavigator(NavigableWidgets[NewIndex], NewIndex);
	}
	else if (bWrapAround)
	{
		NavigateEnd();
	}
}

void UFaethUserWidget::NavigateStart()
{
	UpdateNavigator(NavigableWidgets[0], 0);
}

void UFaethUserWidget::NavigateEnd()
{
	UpdateNavigator(NavigableWidgets[NavigableWidgets.Num()], NavigableWidgets.Num());
}

FNavigationReply UFaethUserWidget::NativeOnNavigation(const FGeometry& MyGeometry, const FNavigationEvent& InNavigationEvent, const FNavigationReply& InDefaultReply)
{
	FNavigationReply NavReply = Super::NativeOnNavigation(MyGeometry, InNavigationEvent, InDefaultReply);
	
	if (NavReply.GetBoundaryRule() == EUINavigationRule::Explicit)
	{
		NavReply.GetFocusRecipient();
	}

	return NavReply;
}

void UFaethUserWidget::UpdateNavigator(UWidget* NewWidget, int NewIndex)
{
	WidgetNavigator.Widget = NewWidget;
	WidgetNavigator.Index = NewIndex;
}
