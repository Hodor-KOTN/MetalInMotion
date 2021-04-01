#pragma once

#include "DebugUtilities.generated.h"

UCLASS(Abstract)
class UDebugUtilities : public UObject
{
	GENERATED_BODY()

public:
	static float HorizontalNameOffset;
	static float HorizontalValueOffset;
	static float LineHeight;

	static FLinearColor DrawColor;

	static void DrawStatistic(class UCanvas* canvas, float& yPos, const TCHAR* name, const FText& value, const UFont* font, const FLinearColor& color);

	FORCEINLINE static void DrawStatistic(UCanvas* canvas, float& yPos, const TCHAR* name, const FText& value, const FLinearColor& color = DrawColor)
	{
		DrawStatistic(canvas, yPos, name, value, GEngine->GetMediumFont(), color);
	}
	FORCEINLINE static void DrawStatistic(UCanvas* canvas, float& yPos, const TCHAR* name, const FString& value, const FLinearColor& color = DrawColor)
	{
		DrawStatistic(canvas, yPos, name, FText::FromString(value), GEngine->GetMediumFont(), color);
	}
	FORCEINLINE static void DrawStatistic(UCanvas* canvas, float& yPos, const TCHAR* name, const FName& value, const FLinearColor& color = DrawColor)
	{
		DrawStatistic(canvas, yPos, name, FText::FromName(value), GEngine->GetMediumFont(), color);
	}
	FORCEINLINE static void DrawStatistic(UCanvas* canvas, float& yPos, const TCHAR* name, float value, const FLinearColor& color = DrawColor)
	{
		DrawStatistic(canvas, yPos, name, FText::AsNumber(value), GEngine->GetMediumFont(), color);
	}
	FORCEINLINE static void DrawStatistic(UCanvas* canvas, float& yPos, const TCHAR* name, bool value, const FLinearColor& trueColor = FLinearColor::Green, const FLinearColor& falseColor = FLinearColor::Red)
	{
		DrawStatistic(canvas, yPos, name, FText::FromString(value ? TEXT("true") : TEXT("false")), GEngine->GetMediumFont(), value ? trueColor : falseColor);
	}
};
