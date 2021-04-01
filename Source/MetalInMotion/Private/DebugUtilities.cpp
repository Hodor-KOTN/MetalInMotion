#include "DebugUtilities.h"
#include "CanvasItem.h"
#include "Engine/Canvas.h"

FLinearColor UDebugUtilities::DrawColor = FLinearColor::White;
float UDebugUtilities::HorizontalNameOffset = 50.f;
float UDebugUtilities::HorizontalValueOffset = 150.f;
float UDebugUtilities::LineHeight = 16.f;

void UDebugUtilities::DrawStatistic(UCanvas* canvas, float& yPos, const TCHAR* name, const FText& value, const UFont* font, const FLinearColor& color)
{
	FCanvasTextItem item0(FVector2D(HorizontalNameOffset, yPos), FText::FromString(name), font, color);
	item0.EnableShadow(FLinearColor::Black);
	canvas->DrawItem(item0);

	FCanvasTextItem item1(FVector2D(HorizontalValueOffset, yPos), value, font, color);
	item0.EnableShadow(FLinearColor::Black);
	canvas->DrawItem(item1);

	yPos += LineHeight;
}