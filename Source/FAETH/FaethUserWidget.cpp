#include "FaethUserWidget.h"
#include "Blueprint/WidgetTree.h"

TArray<UWidget*> UFaethUserWidget::GetChildren()
{
	TArray<UWidget*> Children;
	WidgetTree.Get()->GetAllWidgets(Children);

	return Children;
}

TArray<UWidget*> UFaethUserWidget::GetChildrenOfClass(TSubclassOf<UWidget> WidgetClass)
{
	TArray<UWidget*> Children = GetChildren();
	TArray<UWidget*> ClassChildren;

	for (int i = 0; i < Children.Num(); ++i)
	{
		if (Children[i]->IsA(WidgetClass))
		{
			ClassChildren.Add(Children[i]);
		}
	}

	return ClassChildren;
}

FNavigationReply UFaethUserWidget::NativeOnNavigation(const FGeometry& MyGeometry, const FNavigationEvent& InNavigationEvent, const FNavigationReply& InDefaultReply)
{
	FNavigationReply NavReply = Super::NativeOnNavigation(MyGeometry, InNavigationEvent, InDefaultReply);
	
	TArray<UWidget*> Children = GetChildren();

	for (int i = 0; i < Children.Num(); ++i)
	{
		
	}

	OnNavigation();

	return NavReply;
}

void UFaethUserWidget::UpdateNavigator(UWidget* NewWidget, int NewIndex)
{
	WidgetNavigator.PreviousWidget = WidgetNavigator.CurrentWidget;
	WidgetNavigator.CurrentWidget = NewWidget;
	WidgetNavigator.Index = NewIndex;
}
